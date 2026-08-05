#include "PlayerControllerComponent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "AnimationComponent.h"
#include "RigidbodyComponent.h"
#include "Vector2.h"

PlayerControllerComponent::PlayerControllerComponent()
{
    m_MoveSpeed = 300.0f;
    m_Rigidbody = nullptr;
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
    if (m_Rigidbody == nullptr)
    {
        m_Rigidbody =
            GetOwner()->GetComponent<RigidbodyComponent>();

        if (m_Rigidbody == nullptr)
            return;
    }

    Math::Vector2 direction(0.0f, 0.0f);

    if (InputManager::GetKey(Key::W))
    {
        direction.Y -= 1.0f;
    }

    if (InputManager::GetKey(Key::S))
    {
        direction.Y += 1.0f;
    }

    if (InputManager::GetKey(Key::A))
    {
        direction.X -= 1.0f;
    }

    if (InputManager::GetKey(Key::D))
    {
        direction.X += 1.0f;
    }

    bool moving =
        direction.X != 0.0f ||
        direction.Y != 0.0f;

    if (moving)
    {
        direction = direction.Normalize();
    }

    m_Rigidbody->SetVelocity(
        direction * m_MoveSpeed);

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