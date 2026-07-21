#include "Player.h"

#include "Assets.h"
#include "ResourceManager.h"

#include "SpriteComponent.h"
#include "PlayerControllerComponent.h"

Player::Player()
{
    SetName("Player");
    SetTag("Player");

    m_SpriteComponent = nullptr;
    m_PlayerController = nullptr;
}

Player::~Player()
{

}

void Player::Initialize()
{
    GetTransform().Position =
        Math::Vector2(300.0f, 200.0f);

    GetTransform().Size =
        Math::Vector2(128.0f, 128.0f);

    m_SpriteComponent =
        AddComponent<SpriteComponent>();

    m_SpriteComponent->LoadTexture(
        Assets::Textures::PLAYER);

    m_SpriteComponent->SetSize(128, 128);

    m_PlayerController =
        AddComponent<PlayerControllerComponent>();

    m_PlayerController->SetMoveSpeed(300.0f);
}