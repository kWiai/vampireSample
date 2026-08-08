#pragma once

#include <string>

#include "Vector2.h"
#include "CollisionLayer.h"

struct EntityAnimationDefinition
{

    bool HasAnimation = false;

    std::wstring Texture;

    int FrameCount = 1;
    int FrameWidth = 0;
    int FrameHeight = 0;

    float FrameDuration = 0.1f;

    bool Loop = true;
};

struct EntityDefinition
{
    std::string Name = "GameObject";
    // -------------------------
    // Transform
    // -------------------------

    Math::Vector2 Position =
        Math::Vector2(0.0f, 0.0f);

    Math::Vector2 Size =
        Math::Vector2(32.0f, 32.0f);


    // -------------------------
    // Sprite
    // -------------------------

    bool HasSprite = false;

    std::wstring Texture;


    // -------------------------
    // Animation
    // -------------------------

    bool HasAnimation = false;

    EntityAnimationDefinition Idle;

    EntityAnimationDefinition Walk;


    // -------------------------
    // Rigidbody
    // -------------------------

    bool HasRigidbody = false;

    bool UseGravity = false;

    float GravityScale = 1.0f;

    bool Kinematic = false;


    // -------------------------
    // Collider
    // -------------------------

    bool HasCollider = false;

    Math::Vector2 ColliderSize =
        Math::Vector2(32.0f, 32.0f);

    Math::Vector2 ColliderOffset =
        Math::Vector2(0.0f, 0.0f);

    bool Trigger = false;

    CollisionLayer Layer =
        CollisionLayer::Default;


    // -------------------------
    // Player Controller
    // -------------------------

    bool HasPlayerController = false;

    float MoveSpeed = 300.0f;
};