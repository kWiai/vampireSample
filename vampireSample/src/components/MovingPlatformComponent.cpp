#include "MovingPlatformComponent.h"

#include "src/core/GameObject.h"

MovingPlatformComponent::MovingPlatformComponent()
{
    m_CurrentPoint = 0;
    m_Speed = 100.0f;
    m_Loop = true;

    m_PreviousPosition = Math::Vector2(0.0f, 0.0f);
    m_Delta = Math::Vector2(0.0f, 0.0f);
}

MovingPlatformComponent::~MovingPlatformComponent()
{
}

void MovingPlatformComponent::Update(float deltaTime)
{
    m_PreviousPosition =
        GetOwner()->GetTransform().Position;

    if (m_Points.empty())
    {
        m_Delta = Math::Vector2(0.0f, 0.0f);
        return;
    }

    if (m_CurrentPoint < 0 ||
        m_CurrentPoint >= static_cast<int>(m_Points.size()))
    {
        m_Delta = Math::Vector2(0.0f, 0.0f);
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

        m_Delta =
            GetOwner()->GetTransform().Position -
            m_PreviousPosition;

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

    m_Delta =
        GetOwner()->GetTransform().Position -
        m_PreviousPosition;
}

void MovingPlatformComponent::AddPoint(
    const Math::Vector2& point)
{
    m_Points.push_back(point);
}
const Math::Vector2&
MovingPlatformComponent::GetPreviousPosition() const
{
    return m_PreviousPosition;
}

const Math::Vector2&
MovingPlatformComponent::GetDelta() const
{
    return m_Delta;
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