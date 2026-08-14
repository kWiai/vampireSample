#include "Player.h"

#include "src/components/Assets.h"
#include "src/utilits/ResourceManager.h"

#include "src/components/SpriteComponent.h"
#include "src/components/PlayerControllerComponent.h"
#include "src/components/AnimationComponent.h"
#include "PlayerAnimations.h"
#include "src/components/BoxColliderComponent.h"
#include "src/components/RigidbodyComponent.h"

Player::Player()
{
    SetName("Player");
    SetTag("Player");

    m_SpriteComponent = nullptr;
    m_PlayerController = nullptr;
    m_Animation = nullptr;
    m_Rigidbody = nullptr;
}

Player::~Player()
{

}

void Player::Initialize()
{
    GetTransform().Position =
        Math::Vector2(0.0f, 0.0f);

    GetTransform().Size =
        Math::Vector2(160.0f, 160.0f);


    //-----------------------------------
    // Sprite
    //-----------------------------------
    auto collider =
        AddComponent<BoxColliderComponent>();
    collider->SetLayer(
        CollisionLayer::Player);

    collider->SetSize(
        160,
        160);

    m_SpriteComponent =
        AddComponent<SpriteComponent>();

    m_SpriteComponent->LoadTexture(
        Assets::Textures::PLAYER);

    m_SpriteComponent->SetSize(160, 160);


    //-----------------------------------
    // Animation
    //-----------------------------------

    m_Animation =
        AddComponent<AnimationComponent>();

    m_Animation->AddAnimation(
        PlayerAnimations::CreateIdle());

    m_Animation->AddAnimation(
        PlayerAnimations::CreateWalk());

    m_Animation->Play("Idle");

    m_Rigidbody =
        AddComponent<RigidbodyComponent>();

    m_Rigidbody->SetUseGravity(false);

    m_Rigidbody->SetKinematic(false);

    m_PlayerController =
        AddComponent<PlayerControllerComponent>();

    m_PlayerController->SetMoveSpeed(300.0f);
}