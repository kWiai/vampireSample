#include "ProjectileComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "BoxColliderComponent.h"
#include "Damage.h"
#include "Render.h"
#include "Camera.h"

ProjectileComponent::ProjectileComponent()
    : m_Direction(0, 0)
    , m_Speed(0)
    , m_Damage(10)
    , m_MaxDistance(500)
    , m_TraveledDistance(0)
{
}

ProjectileComponent::~ProjectileComponent() {}

void ProjectileComponent::SetDirection(const Math::Vector2& dir)
{
    m_Direction = dir.Normalize();
}

void ProjectileComponent::SetSpeed(float speed) { m_Speed = speed; }
void ProjectileComponent::SetDamage(float damage) { m_Damage = damage; }
void ProjectileComponent::SetMaxDistance(float distance) { m_MaxDistance = distance; }

void ProjectileComponent::Update(float deltaTime)
{
    if (!GetOwner() || !GetOwner()->IsActive()) return;

    GetOwner()->GetTransform().Position += m_Direction * m_Speed * deltaTime;
    m_TraveledDistance += m_Speed * deltaTime;

    auto scene = GetOwner()->GetScene();
    if (!scene) return;

    auto myCollider = GetOwner()->GetComponent<BoxColliderComponent>();
    if (!myCollider) return;

    auto enemies = scene->FindAllByTag("Enemy");
    for (auto* enemy : enemies)
    {
        if (!enemy || !enemy->IsActive()) continue;
        auto enemyCollider = enemy->GetComponent<BoxColliderComponent>();
        if (!enemyCollider) continue;

        if (myCollider->GetBounds().Intersects(enemyCollider->GetBounds()))
        {
            Damage::Apply(GetOwner(), enemy, m_Damage);
            GetOwner()->Destroy();  
            return;
        }
    }

    if (m_TraveledDistance >= m_MaxDistance)
    {
        GetOwner()->Destroy();     
    }
}

void ProjectileComponent::Render(Renderer& renderer, const Camera& camera)
{
    if (!GetOwner() || !GetOwner()->IsActive()) return;
    auto pos = GetOwner()->GetTransform().Position;
   
    auto size = GetOwner()->GetTransform().Size;

    // Жёлтый квадрат (снаряд)
    renderer.DrawFilledRectangle(pos.X, pos.Y, size.X, size.Y, camera, 255, 255, 0, 255);
}