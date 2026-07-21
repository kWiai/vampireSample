#include "PlayerControllerComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "InputManager.h"

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

    if (InputManager::GetKey(Key::W))
    {
        transform.Position.Y -= m_MoveSpeed * deltaTime;
    }

    if (InputManager::GetKey(Key::S))
    {
        transform.Position.Y += m_MoveSpeed * deltaTime;
    }

    if (InputManager::GetKey(Key::A))
    {
        transform.Position.X -= m_MoveSpeed * deltaTime;
    }

    if (InputManager::GetKey(Key::D))
    {
        transform.Position.X += m_MoveSpeed * deltaTime;
    }
}