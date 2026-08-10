#include "EnemyControllerComponent.h"

#include "GameObject.h"

EnemyControllerComponent::EnemyControllerComponent()
{
    m_CurrentPoint = 0;

    m_Speed = 100.0f;

    m_ViewRadius = 300.0f;

    m_Target = nullptr;

    m_State = State::Patrol;
}

EnemyControllerComponent::~EnemyControllerComponent()
{
}

void EnemyControllerComponent::Update(float deltaTime)
{
    if (GetOwner() == nullptr)
        return;

    if (m_Target != nullptr)
    {
        if (IsTargetInRange())
        {
            m_State = State::Chase;
        }
        else
        {
            m_State = State::Patrol;
        }
    }

    switch (m_State)
    {
    case State::Patrol:
        UpdatePatrol(deltaTime);
        break;

    case State::Chase:
        UpdateChase(deltaTime);
        break;
    }
}

void EnemyControllerComponent::UpdatePatrol(
    float deltaTime)
{
    if (m_Points.empty())
        return;

    if (m_CurrentPoint < 0 ||
        m_CurrentPoint >=
        static_cast<int>(m_Points.size()))
    {
        return;
    }

    MoveTowards(
        m_Points[m_CurrentPoint],
        deltaTime);

    Math::Vector2 position =
        GetOwner()->GetTransform().Position;

    Math::Vector2 direction =
        m_Points[m_CurrentPoint] - position;

    if (direction.Length() <= 1.0f)
    {
        GetOwner()->GetTransform().Position =
            m_Points[m_CurrentPoint];

        m_CurrentPoint++;

        if (m_CurrentPoint >=
            static_cast<int>(m_Points.size()))
        {
            m_CurrentPoint = 0;
        }
    }
}

void EnemyControllerComponent::UpdateChase(
    float deltaTime)
{
    if (m_Target == nullptr)
        return;

    MoveTowards(
        m_Target->GetTransform().Position,
        deltaTime);
}

bool EnemyControllerComponent::IsTargetInRange() const
{
    if (m_Target == nullptr)
        return false;

    Math::Vector2 position =
        GetOwner()->GetTransform().Position;

    Math::Vector2 targetPosition =
        m_Target->GetTransform().Position;

    Math::Vector2 direction =
        targetPosition - position;

    return direction.Length() <= m_ViewRadius;
}

void EnemyControllerComponent::MoveTowards(
    const Math::Vector2& target,
    float deltaTime)
{
    Math::Vector2 position =
        GetOwner()->GetTransform().Position;

    Math::Vector2 direction =
        target - position;

    float distance =
        direction.Length();

    if (distance <= 0.01f)
        return;

    direction =
        direction.Normalize();

    float movement =
        m_Speed * deltaTime;

    if (movement >= distance)
    {
        GetOwner()->GetTransform().Position =
            target;
    }
    else
    {
        GetOwner()->GetTransform().Position +=
            direction * movement;
    }
}

void EnemyControllerComponent::AddPoint(
    const Math::Vector2& point)
{
    m_Points.push_back(point);
}

void EnemyControllerComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}

float EnemyControllerComponent::GetSpeed() const
{
    return m_Speed;
}

void EnemyControllerComponent::SetViewRadius(
    float radius)
{
    m_ViewRadius = radius;
}

float EnemyControllerComponent::GetViewRadius() const
{
    return m_ViewRadius;
}

void EnemyControllerComponent::SetTarget(
    GameObject* target)
{
    m_Target = target;
}