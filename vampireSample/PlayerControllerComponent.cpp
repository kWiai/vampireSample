#include "PlayerControllerComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "InputManager.h"
#include "AnimationComponent.h"

PlayerControllerComponent::PlayerControllerComponent()
{
    m_MoveSpeed = 300.0f;
}

PlayerControllerComponent::~PlayerControllerComponent()
{

}

void PlayerControllerComponent::SetMoveSpeed(float speed)
{
    m_MoveSpeed = speed;
}

void PlayerControllerComponent::Update(float deltaTime)
{
    auto& transform = GetTransform();

    bool moving = false;

    if (InputManager::GetKey(Key::W))
    {
        transform.Position.Y -= m_MoveSpeed * deltaTime;
        moving = true;
    }

    if (InputManager::GetKey(Key::S))
    {
        transform.Position.Y += m_MoveSpeed * deltaTime;
        moving = true;
    }

    if (InputManager::GetKey(Key::A))
    {
        transform.Position.X -= m_MoveSpeed * deltaTime;
        moving = true;
    }

    if (InputManager::GetKey(Key::D))
    {
        transform.Position.X += m_MoveSpeed * deltaTime;
        moving = true;
    }

    auto animation =
        GetOwner()->GetComponent<AnimationComponent>();

    if (animation == nullptr)
        return;

    if (moving)
    {
        animation->Play("Walk");
    }
    else
    {
        animation->Play("Idle");
    }
}