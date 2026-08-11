#pragma once

#include <string>
#include <vector>
#include <iostream>
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

    float Mass = 1.0f;

    bool Kinematic = false;

    Math::Vector2 InitialVelocity =
        Math::Vector2(0.0f, 0.0f);


    // -------------------------
    // Collider
    // -------------------------

    bool HasCollider = false;

    Math::Vector2 ColliderSize =
        Math::Vector2(32.0f, 32.0f);

    Math::Vector2 ColliderOffset =
        Math::Vector2(0.0f, 0.0f);

    bool Trigger = false;

    bool IsPassable = false;

    CollisionLayer Layer =
        CollisionLayer::Default;


    // -------------------------
    // Player Controller
    // -------------------------

    bool HasPlayerController = false;

    float MoveSpeed = 300.0f;

    // -------------------------
    // Damage
    // -------------------------

    bool HasDamage = false;

    float Damage = 0.0f;

    // -------------------------
// Health
// -------------------------

    bool HasHealth = false;

    float MaxHealth = 100.0f;

    float Health = 100.0f;

    // -------------------------
// Moving Platform
// -------------------------

    bool HasMovingPlatform = false;

    float MovementSpeed = 100.0f;

    bool MovementLoop = true;

    std::vector<Math::Vector2> MovementPoints;

    // -------------------------
// Enemy
// -------------------------

    bool HasEnemyController = false;

    float EnemySpeed = 100.0f;

    float EnemyViewRadius = 300.0f;

    std::vector<Math::Vector2> EnemyPoints;
};

struct EntityMovementPoint
{
    Math::Vector2 Position =
        Math::Vector2(0.0f, 0.0f);
};