#pragma once
#include "Component.h"
#include "Vector2.h"

class Renderer;
class Camera;

class ProjectileComponent : public Component
{
public:
    ProjectileComponent();
    ~ProjectileComponent() override;

    void Update(float deltaTime) override;
    void Render(Renderer& renderer, const Camera& camera) override;

    void SetDirection(const Math::Vector2& direction);
    void SetSpeed(float speed);
    void SetDamage(float damage);
    void SetMaxDistance(float distance);

private:
    Math::Vector2 m_Direction;
    float m_Speed;
    float m_Damage;
    float m_MaxDistance;
    float m_TraveledDistance;
};