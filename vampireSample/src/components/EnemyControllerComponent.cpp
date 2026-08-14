#include "EnemyControllerComponent.h"
#include "src/core/GameObject.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "src/core/Scene.h"
#include "src/physics/PhysicsWorld.h"
#include "src/physics/RaycastHit.h"
#include <cmath>
#include "HealthComponent.h"

// Глобальный флаг (объявлен где-то в главном файле)
extern bool g_IsSideView;

EnemyControllerComponent::EnemyControllerComponent()
{
    m_CurrentPoint = 0;
    m_Speed = 100.0f;
    m_ViewRadius = 300.0f;
    m_Target = nullptr;
    m_State = State::Patrol;
}

EnemyControllerComponent::~EnemyControllerComponent() {}

void EnemyControllerComponent::SetJumpForce(float force) { m_JumpForce = force; }

// ---------- Определяем режим ----------
bool EnemyControllerComponent::IsSideView() const
{
    return g_IsSideView;
}

// ---------- Проверка земли (только для Side-View) ----------
bool EnemyControllerComponent::IsGrounded() const
{
    if (!m_Collider) return false;
    Physics::AABB bounds = m_Collider->GetBounds();
    Math::Vector2 origin((bounds.Min.X + bounds.Max.X) * 0.5f, bounds.Max.Y + 2.0f);
    Scene* scene = GetOwner()->GetScene();
    if (!scene) return false;
    RaycastHit hit;
    scene->GetPhysics().Raycast(origin, Math::Vector2(0.0f, 1.0f), 6.0f, hit, *scene, GetOwner());
    return hit.Hit;
}

// ---------- Проверка стены впереди (только для Side-View) ----------
bool EnemyControllerComponent::IsWallAhead(float distance) const
{
    if (!m_Rigidbody || !m_Collider) return false;

    float dirX = 0.0f;
    Math::Vector2 velocity = m_Rigidbody->GetVelocity();
    if (fabs(velocity.X) > 1.0f) {
        dirX = (velocity.X > 0) ? 1.0f : -1.0f;
    }
    else {
        Math::Vector2 target;
        if (m_State == State::Patrol && !m_Points.empty())
            target = m_Points[m_CurrentPoint];
        else if (m_Target)
            target = m_Target->GetTransform().Position;
        else
            return false;

        Math::Vector2 dir = target - GetOwner()->GetTransform().Position;
        if (fabs(dir.X) < 0.1f) return false;
        dirX = (dir.X > 0) ? 1.0f : -1.0f;
    }

    Physics::AABB bounds = m_Collider->GetBounds();
    float offsetX = (bounds.Max.X - bounds.Min.X) * 0.5f + 2.0f;
    Math::Vector2 originTop(
        (bounds.Min.X + bounds.Max.X) * 0.5f + dirX * offsetX,
        bounds.Min.Y + 5.0f
    );
    Math::Vector2 originBottom(
        (bounds.Min.X + bounds.Max.X) * 0.5f + dirX * offsetX,
        bounds.Max.Y - 5.0f
    );

    Scene* scene = GetOwner()->GetScene();
    if (!scene) return false;

    uint32_t ignoreLayers = 0;
    ignoreLayers |= (1 << static_cast<int>(CollisionLayer::Enemy));
    ignoreLayers |= (1 << static_cast<int>(CollisionLayer::Player));

    RaycastHit hit;
    bool hitTop = scene->GetPhysics().Raycast(
        originTop,
        Math::Vector2(dirX, 0.0f),
        distance,
        hit,
        *scene,
        GetOwner(),     // игнорируем самого врага (старый параметр)
        ignoreLayers    // игнорируем всех врагов и игрока по слоям
    );
    bool hitBottom = scene->GetPhysics().Raycast(
        originBottom,
        Math::Vector2(dirX, 0.0f),
        distance,
        hit,
        *scene,
        GetOwner(),
        ignoreLayers
    );
    return hitTop || hitBottom;
}

void EnemyControllerComponent::Render(Renderer& renderer, const Camera& camera)
{
    auto health = GetOwner()->GetComponent<HealthComponent>();
    if (health) {
        health->DrawHealthBar(renderer, camera, Math::Vector2(0.0f, 30.0f), Math::Vector2(40.0f, 5.0f), false);
    }
}
// ---------- Прыжок (только Side-View) ----------
void EnemyControllerComponent::TryJump()
{
    if (!IsSideView()) return;
    if (!m_Rigidbody || m_Rigidbody->IsKinematic()) return;
    if (!IsGrounded()) return;
    if (!IsWallAhead(25.0f)) return;

    Math::Vector2 vel = m_Rigidbody->GetVelocity();
    vel.Y = -m_JumpForce;
    m_Rigidbody->SetVelocity(vel);
}

// ---------- Движение к цели ----------
void EnemyControllerComponent::MoveTowards(const Math::Vector2& target, float deltaTime)
{
    if (IsSideView())
    {
        // ----- Боковой вид: используем Rigidbody, только X -----
        if (!m_Rigidbody) return;
        float dx = target.X - GetOwner()->GetTransform().Position.X;
        if (fabs(dx) < 0.5f) return; // почти на месте – не дёргаемся

        float dirX = (dx > 0) ? 1.0f : -1.0f;

        Math::Vector2 velocity = m_Rigidbody->GetVelocity();
        velocity.X = dirX * m_Speed;
        m_Rigidbody->SetVelocity(velocity);
    }
    else
    {
        // ----- Вид сверху: прямое перемещение (старый способ) -----
        Math::Vector2 position = GetOwner()->GetTransform().Position;
        Math::Vector2 dir = target - position;
        float distance = dir.Length();
        if (distance <= 0.01f) return;
        dir = dir.Normalize();

        float movement = m_Speed * deltaTime;
        if (movement >= distance)
            GetOwner()->GetTransform().Position = target;
        else
            GetOwner()->GetTransform().Position += dir * movement;
    }
}

// ---------- Патрулирование ----------
void EnemyControllerComponent::UpdatePatrol(float deltaTime)
{
    if (m_Points.empty()) return;
    if (m_CurrentPoint < 0 || m_CurrentPoint >= static_cast<int>(m_Points.size()))
        return;

    MoveTowards(m_Points[m_CurrentPoint], deltaTime);

    // Проверка достижения точки
    Math::Vector2 position = GetOwner()->GetTransform().Position;
    Math::Vector2 direction = m_Points[m_CurrentPoint] - position;

    bool reached = false;
    if (IsSideView())
    {
        // В боковом виде проверяем только X
        reached = (fabs(direction.X) <= 10.0f);
    }
    else
    {
        // В топ-дауне проверяем полное расстояние
        reached = (direction.Length() <= 1.0f);
    }

    if (reached)
    {
        m_CurrentPoint++;
        if (m_CurrentPoint >= static_cast<int>(m_Points.size()))
            m_CurrentPoint = 0;
    }
}

// ---------- Преследование ----------
void EnemyControllerComponent::UpdateChase(float deltaTime)
{
    if (m_Target == nullptr) return;
    MoveTowards(m_Target->GetTransform().Position, deltaTime);
}

// ---------- Проверка дальности до цели ----------
bool EnemyControllerComponent::IsTargetInRange() const
{
    if (!m_Target) return false;
    Math::Vector2 delta = m_Target->GetTransform().Position - GetOwner()->GetTransform().Position;
    return delta.Length() <= m_ViewRadius;
}


// ---------- Основной Update ----------
void EnemyControllerComponent::Update(float deltaTime)
{

    auto health = GetOwner()->GetComponent<HealthComponent>();
    if (health && health->IsDead())
    {
        GetOwner()->Destroy();   // <-- вместо SetActive(false)
        return;
    }

    // Кешируем компоненты (только если Side-View)
    if (IsSideView())
    {
        if (!m_Rigidbody)
            m_Rigidbody = GetOwner()->GetComponent<RigidbodyComponent>();
        if (!m_Collider)
            m_Collider = GetOwner()->GetComponent<BoxColliderComponent>();
        if (!m_Rigidbody) return; // без физики в Side-View не работаем
    }

    // Определяем состояние
    if (m_Target != nullptr && IsTargetInRange())
        m_State = State::Chase;
    else
        m_State = State::Patrol;

    switch (m_State)
    {
    case State::Patrol:
        UpdatePatrol(deltaTime);
        break;
    case State::Chase:
        UpdateChase(deltaTime);
        break;
    }

    // Прыжок только в Side-View
    if (IsSideView())
        TryJump();
}

// ---------- Остальные геттеры/сеттеры ----------
void EnemyControllerComponent::AddPoint(const Math::Vector2& point) { m_Points.push_back(point); }
void EnemyControllerComponent::SetSpeed(float speed) { m_Speed = speed; }
float EnemyControllerComponent::GetSpeed() const { return m_Speed; }
void EnemyControllerComponent::SetViewRadius(float radius) { m_ViewRadius = radius; }
float EnemyControllerComponent::GetViewRadius() const { return m_ViewRadius; }
void EnemyControllerComponent::SetTarget(GameObject* target) { m_Target = target; }