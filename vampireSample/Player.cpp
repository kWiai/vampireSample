#include "Player.h"

#include "Assets.h"
#include "ResourceManager.h"

#include "SpriteComponent.h"
#include "PlayerControllerComponent.h"
#include "Animation.h"
#include "AnimationComponent.h"

Player::Player()
{
    SetName("Player");
    SetTag("Player");

    m_SpriteComponent = nullptr;
    m_PlayerController = nullptr;
    m_Animation = nullptr;
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


    //-----------------------------------
    // Sprite
    //-----------------------------------

    m_SpriteComponent =
        AddComponent<SpriteComponent>();

    m_SpriteComponent->LoadTexture(
        Assets::Textures::PLAYER);

    m_SpriteComponent->SetSize(128, 128);


    //-----------------------------------
    // Animation
    //-----------------------------------

    m_Animation =
        AddComponent<AnimationComponent>();


    Animation walk;

    walk.SetName("Walk");


    walk.AddFrame(
        Math::Rectangle(
            0,
            0,
            256,
            256),
        0.08f);

    walk.AddFrame(
        Math::Rectangle(
            256,
            0,
            256,
            256),
        0.08f);

    walk.AddFrame(
        Math::Rectangle(
            512,
            0,
            256,
            256),
        0.08f);

    walk.AddFrame(
        Math::Rectangle(
            768,
            0,
            256,
            256),
        0.08f);

    walk.AddFrame(
        Math::Rectangle(
            1024,
            0,
            256,
            256),
        0.08f);

    walk.AddFrame(
        Math::Rectangle(
            1280,
            0,
            256,
            256),
        0.08f);

    walk.AddFrame(
        Math::Rectangle(
            1536,
            0,
            256,
            256),
        0.08f);

    walk.AddFrame(
        Math::Rectangle(
            1792,
            0,
            256,
            256),
        0.08f);


    walk.SetLoop(true);


    m_Animation->AddAnimation(walk);

    m_Animation->Play("Walk");


    //-----------------------------------
    // Controller
    //-----------------------------------

    m_PlayerController =
        AddComponent<PlayerControllerComponent>();

    m_PlayerController->SetMoveSpeed(300.0f);
}