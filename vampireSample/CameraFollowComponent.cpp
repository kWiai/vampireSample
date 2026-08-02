#include "CameraFollowComponent.h"

#include "GameObject.h"

#include <windows.h>

#include "CameraComponent.h"

CameraFollowComponent::CameraFollowComponent()
{
    m_Target = nullptr;

    m_Offset = Math::Vector2();

    m_FollowX = true;

    m_FollowY = true;
}

CameraFollowComponent::~CameraFollowComponent()
{

}

void CameraFollowComponent::Update(float deltaTime)
{
    if (GetOwner() == nullptr)
        return;
    
    if (m_Target == nullptr)
        return;
    
    auto camera =
        GetOwner()->GetComponent<CameraComponent>();
    
    if (camera == nullptr)
        return;
    
    Math::Vector2 target =
        m_Target->GetTransform().Position;
    
    Math::Vector2 center =
        camera->GetCamera().GetCenter();
    
    Math::Vector2 position =
        target;
    
    if (m_FollowX)
    {
        position.X =
            target.X - center.X;
    }
    
    if (m_FollowY)
    {
        position.Y =
            target.Y - center.Y;
    }
    
    position += m_Offset;
    
    GetOwner()->GetTransform().Position =
        position;
    camera->GetCamera().SetPosition(position);

}

void CameraFollowComponent::SetTarget(GameObject* target)
{
    m_Target = target;
}

GameObject* CameraFollowComponent::GetTarget() const
{
    return m_Target;
}

void CameraFollowComponent::SetOffset(
    const Math::Vector2& offset)
{
    m_Offset = offset;
}

const Math::Vector2&
CameraFollowComponent::GetOffset() const
{
    return m_Offset;
}

void CameraFollowComponent::SetFollowX(bool follow)
{
    m_FollowX = follow;
}

void CameraFollowComponent::SetFollowY(bool follow)
{
    m_FollowY = follow;
}