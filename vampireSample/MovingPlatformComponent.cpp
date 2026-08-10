#include "MovingPlatformComponent.h"

#include "GameObject.h"

MovingPlatformComponent::MovingPlatformComponent()
{
    m_CurrentPoint = 0;
    m_Speed = 100.0f;
    m_Loop = true;
}

MovingPlatformComponent::~MovingPlatformComponent()
{
}

void MovingPlatformComponent::Update(float deltaTime)
{
    if (m_Points.empty())
        return;

    if (m_CurrentPoint < 0 ||
        m_CurrentPoint >= static_cast<int>(m_Points.size()))
    {
        return;
    }

    Math::Vector2 currentPosition =
        GetOwner()->GetTransform().Position;

    Math::Vector2 target =
        m_Points[m_CurrentPoint];

    Math::Vector2 direction =
        target - currentPosition;

    float distance =
        direction.Length();

    if (distance <= 0.1f)
    {
        GetOwner()->GetTransform().Position =
            target;

        if (m_CurrentPoint + 1 <
            static_cast<int>(m_Points.size()))
        {
            m_CurrentPoint++;
        }
        else if (m_Loop)
        {
            m_CurrentPoint = 0;
        }

        return;
    }

    direction =
        direction.Normalize();

    float movement =
        m_Speed * deltaTime;

    if (movement >= distance)
    {
        GetOwner()->GetTransform().Position =
            target;

        if (m_CurrentPoint + 1 <
            static_cast<int>(m_Points.size()))
        {
            m_CurrentPoint++;
        }
        else if (m_Loop)
        {
            m_CurrentPoint = 0;
        }
    }
    else
    {
        GetOwner()->GetTransform().Position +=
            direction * movement;
    }
}

void MovingPlatformComponent::AddPoint(
    const Math::Vector2& point)
{
    m_Points.push_back(point);
}

void MovingPlatformComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}

float MovingPlatformComponent::GetSpeed() const
{
    return m_Speed;
}

void MovingPlatformComponent::SetLoop(bool loop)
{
    m_Loop = loop;
}

bool MovingPlatformComponent::GetLoop() const
{
    return m_Loop;
}