#pragma once

#include <vector>

#include "Component.h"
#include "Vector2.h"

class GameObject;

class EnemyControllerComponent : public Component
{
public:

    EnemyControllerComponent();
    ~EnemyControllerComponent() override;

    void Update(float deltaTime) override;

    void AddPoint(
        const Math::Vector2& point);

    void SetSpeed(float speed);
    float GetSpeed() const;

    void SetViewRadius(float radius);
    float GetViewRadius() const;

    void SetTarget(GameObject* target);

private:

    enum class State
    {
        Patrol,
        Chase
    };

private:

    void UpdatePatrol(float deltaTime);

    void UpdateChase(float deltaTime);

    bool IsTargetInRange() const;

    void MoveTowards(
        const Math::Vector2& target,
        float deltaTime);

private:

    std::vector<Math::Vector2> m_Points;

    int m_CurrentPoint;

    float m_Speed;

    float m_ViewRadius;

    GameObject* m_Target;

    State m_State;
};