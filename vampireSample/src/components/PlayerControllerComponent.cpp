#include "PlayerControllerComponent.h"
#include "src/core/GameObject.h"
#include "src/input/InputManager.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "src/physics/PhysicsWorld.h"
#include "src/core/Scene.h"
#include "src/physics/RaycastHit.h"
#include "AnimationComponent.h"
#include <algorithm>
#include "HealthComponent.h"
#include "ProjectileComponent.h"   

void PlayerControllerComponent::FireProjectile()
{
    auto scene = GetOwner()->GetScene();
    if (!scene) return;

    auto projectileObj = std::make_unique<GameObject>();
    projectileObj->SetName("Projectile");
    projectileObj->SetTag("Projectile");
    Math::Vector2 playerSize = GetOwner()->GetTransform().Size; // например, (160, 160)
    Math::Vector2 spawnOffset = playerSize * 0.5f; // (80, 80)
    projectileObj->GetTransform().Position = GetOwner()->GetTransform().Position + spawnOffset;
    projectileObj->GetTransform().Size = Math::Vector2(20.0f, 20.0f);

    // Коллайдер (триггер)
    auto col = projectileObj->AddComponent<BoxColliderComponent>();
    col->SetSize(20.0f, 20.0f);
    col->SetOffset(Math::Vector2(0, 0));
    col->SetTrigger(true);   // триггер, чтобы не мешать физике
    col->SetLayer(CollisionLayer::Default);

    // Компонент снаряда
    auto projComp = projectileObj->AddComponent<ProjectileComponent>();
    projComp->SetDamage(25.0f);
    projComp->SetSpeed(600.0f);
    projComp->SetMaxDistance(700.0f);

    Math::Vector2 vel = m_Rigidbody->GetVelocity();
    Math::Vector2 dir = m_LastDirection;
    if (dir.Length() < 0.01f)
        dir = Math::Vector2(1.0f, 0.0f); // fallback

    projComp->SetDirection(dir);

    scene->AddGameObject(std::move(projectileObj));
}

PlayerControllerComponent::PlayerControllerComponent()
{
}

PlayerControllerComponent::~PlayerControllerComponent()
{
}
void PlayerControllerComponent::Render(Renderer& renderer, const Camera& camera)
{
    auto health = GetOwner()->GetComponent<HealthComponent>();
    if (health) {
        health->DrawHealthBar(renderer, camera, Math::Vector2(20.0f, 20.0f), Math::Vector2(150.0f, 15.0f), true);
    }
}
// ---------- геттеры/сеттеры ----------
void PlayerControllerComponent::SetMoveSpeed(float speed) { m_MoveSpeed = speed; }
float PlayerControllerComponent::GetMoveSpeed() const { return m_MoveSpeed; }

void PlayerControllerComponent::SetJumpForce(float force) { m_JumpForce = force; }
float PlayerControllerComponent::GetJumpForce() const { return m_JumpForce; }

void PlayerControllerComponent::SetSideView(bool enable) { m_IsSideView = enable; }
bool PlayerControllerComponent::IsSideView() const { return m_IsSideView; }

void PlayerControllerComponent::SetAcceleration(float accel) { m_Acceleration = accel; }
void PlayerControllerComponent::SetDeceleration(float decel) { m_Deceleration = decel; }

// ---------- проверка земли ----------
bool PlayerControllerComponent::IsGrounded() const
{
    auto col = GetOwner()->GetComponent<BoxColliderComponent>();
    if (!col) return false;

    // Берём центр коллайдера
    Math::Vector2 center = col->GetCenter();
    float halfHeight = col->GetSize().Y * 0.5f;

    // Луч из центра вниз на половину высоты + небольшой запас (4 пикселя)
    float checkDist = halfHeight + 4.0f;

    Scene* scene = GetOwner()->GetScene();
    if (!scene) return false;

    RaycastHit hit;
    scene->GetPhysics().Raycast(center, Math::Vector2(0.0f, 1.0f), checkDist, hit, *scene, GetOwner());

    // Если луч что-то задел – значит под ногами есть опора
    return hit.Hit;
}

// ---------- главный Update ----------
void PlayerControllerComponent::Update(float deltaTime)
{
    // кешируем Rigidbody
    if (!m_Rigidbody)
    {
        m_Rigidbody = GetOwner()->GetComponent<RigidbodyComponent>();
        if (!m_Rigidbody) return;
    }

    // ввод
    float moveX = (InputManager::GetKey(Key::D) ? 1.0f : 0.0f) - (InputManager::GetKey(Key::A) ? 1.0f : 0.0f);
    float moveY = (InputManager::GetKey(Key::S) ? 1.0f : 0.0f) - (InputManager::GetKey(Key::W) ? 1.0f : 0.0f);
    if (InputManager::GetKeyDown(Key::Space))
    {
        FireProjectile();
    }
    // плавное ускорение по X
    if (moveX != 0.0f)
    {
        m_CurrentSpeedX += moveX * m_Acceleration * deltaTime;
        m_CurrentSpeedX = std::clamp(m_CurrentSpeedX, -m_MoveSpeed, m_MoveSpeed);
    }
    else
    {
        if (m_CurrentSpeedX > 0.0f)
            m_CurrentSpeedX = max(0.0f, m_CurrentSpeedX - m_Deceleration * deltaTime);
        else if (m_CurrentSpeedX < 0.0f)
            m_CurrentSpeedX = min(0.0f, m_CurrentSpeedX + m_Deceleration * deltaTime);
    }

    Math::Vector2 velocity = m_Rigidbody->GetVelocity();

    if (m_IsSideView)
    {
        // боковой вид: горизонталь из плавного ускорения, вертикаль – физика + прыжок
        velocity.X = m_CurrentSpeedX;
        if (std::abs(m_CurrentSpeedX) > 1.0f)
        {
            m_LastDirection = Math::Vector2(m_CurrentSpeedX > 0 ? 1.0f : -1.0f, 0.0f);
        }
        // прыжок (только когда на земле)
        if (InputManager::GetKeyDown(Key::W) && IsGrounded())
            velocity.Y = -m_JumpForce;
    }
    else
    {
        // top?down: плавное движение и по Y тоже
        if (moveY != 0.0f)
        {
            m_CurrentSpeedY += moveY * m_Acceleration * deltaTime;
            m_CurrentSpeedY = std::clamp(m_CurrentSpeedY, -m_MoveSpeed, m_MoveSpeed);
        }
        else
        {
            if (m_CurrentSpeedY > 0.0f)
                m_CurrentSpeedY = max(0.0f, m_CurrentSpeedY - m_Deceleration * deltaTime);
            else if (m_CurrentSpeedY < 0.0f)
                m_CurrentSpeedY = min(0.0f, m_CurrentSpeedY + m_Deceleration * deltaTime);
        }

        Math::Vector2 vel = m_Rigidbody->GetVelocity();
        if (vel.Length() > 1.0f)
        {
            m_LastDirection = vel.Normalize();
        }

        velocity.X = m_CurrentSpeedX;
        velocity.Y = m_CurrentSpeedY;

    }

    m_Rigidbody->SetVelocity(velocity);

    // анимация
    auto anim = GetOwner()->GetComponent<AnimationComponent>();
    if (anim)
    {
        if (std::abs(velocity.X) > 5.0f || (!m_IsSideView && std::abs(velocity.Y) > 5.0f))
            anim->Play("Walk");
        else
            anim->Play("Idle");
    }

    // ---------- отладочный рейкаст (можно удалить) ----------
    auto scene = GetOwner()->GetScene();
    if (scene && (moveX != 0.0f || moveY != 0.0f))
    {
        auto col = GetOwner()->GetComponent<BoxColliderComponent>();
        if (col)
        {
            Physics::AABB bounds = col->GetBounds();
            Math::Vector2 origin = (bounds.Min + bounds.Max) * 0.5f;
            Math::Vector2 dir;
            if (m_IsSideView)
                dir = Math::Vector2(moveX, 0);      // только вбок
            else
                dir = Math::Vector2(moveX, moveY).Normalize();

            RaycastHit hit;
            scene->GetPhysics().Raycast(origin, dir, 300.0f, hit, *scene, GetOwner());
            // результат можно игнорировать
        }
    }
}