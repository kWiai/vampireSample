#include "BoxColliderComponent.h"

#include "GameObject.h"

BoxColliderComponent::BoxColliderComponent()
{
    m_Size = Math::Vector2(32.0f, 32.0f);
    m_Offset = Math::Vector2(0.0f, 0.0f);

    m_IsTrigger = false;
}

BoxColliderComponent::~BoxColliderComponent()
{

}

void BoxColliderComponent::SetSize(
    float width,
    float height)
{
    m_Size = Math::Vector2(width, height);
}

Math::Vector2 BoxColliderComponent::GetSize() const
{
    return m_Size;
}

void BoxColliderComponent::SetOffset(
    const Math::Vector2& offset)
{
    m_Offset = offset;
}

Math::Vector2 BoxColliderComponent::GetOffset() const
{
    return m_Offset;
}

void BoxColliderComponent::SetTrigger(bool trigger)
{
    m_IsTrigger = trigger;
}

bool BoxColliderComponent::IsTrigger() const
{
    return m_IsTrigger;
}

Math::Vector2 BoxColliderComponent::GetMin() const
{
    return
        GetTransform().Position +
        m_Offset;
}

Math::Vector2 BoxColliderComponent::GetMax() const
{
    return
        GetTransform().Position +
        m_Offset +
        m_Size;
}