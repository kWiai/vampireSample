#include "EntityFactory.h"

#include "EntityDefinition.h"

#include "src/core/GameObject.h"

#include "src/components/SpriteComponent.h"
#include "src/components/RigidbodyComponent.h"
#include "src/components/BoxColliderComponent.h"
#include "src/components/PlayerControllerComponent.h"
#include "src/components/AnimationComponent.h"
#include "src/components/AnimationClip.h"
#include "src/utilits/ResourceManager.h"
#include "src/components/DamageOnCollisionComponent.h"
#include "src/components/HealthComponent.h"
#include "src/components/MovingPlatformComponent.h"
#include "src/components/EnemyControllerComponent.h"
#include "src/components/DestroyOnCollisionComponent.h"

std::unique_ptr<GameObject>
EntityFactory::Create(
    const EntityDefinition& definition)
{
    auto object =
        std::make_unique<GameObject>();

    object->SetName(
        definition.Name);


    // -------------------------
    // Transform
    // -------------------------

    object->GetTransform().Position =
        definition.Position;

    object->GetTransform().Size =
        definition.Size;


    // -------------------------
    // Sprite
    // -------------------------

    if (definition.HasSprite)
    {
        auto sprite =
            object->AddComponent<SpriteComponent>();

        if (!definition.Texture.empty())
        {
            sprite->LoadTexture(
                definition.Texture);
        }

        sprite->SetSize(
            definition.Size.X,
            definition.Size.Y);
    }

    // -------------------------
// Animation
// -------------------------

    if (definition.HasAnimation)
    {
        auto animation =
            object->AddComponent<AnimationComponent>();

        if (definition.Idle.HasAnimation)
        {
            AnimationClip clip;

            clip.SetName("Idle");

            clip.SetTexture(
                ResourceManager::LoadTexture(
                    definition.Idle.Texture));

            clip.GenerateHorizontal(
                definition.Idle.FrameCount,
                definition.Idle.FrameWidth,
                definition.Idle.FrameHeight,
                definition.Idle.FrameDuration);

            clip.SetLoop(
                definition.Idle.Loop);

            animation->AddAnimation(clip);
        }

        if (definition.Walk.HasAnimation)
        {
            AnimationClip clip;

            clip.SetName("Walk");

            clip.SetTexture(
                ResourceManager::LoadTexture(
                    definition.Walk.Texture));

            clip.GenerateHorizontal(
                definition.Walk.FrameCount,
                definition.Walk.FrameWidth,
                definition.Walk.FrameHeight,
                definition.Walk.FrameDuration);

            clip.SetLoop(
                definition.Walk.Loop);

            animation->AddAnimation(clip);
        }

        animation->Play("Idle");
    }

    // -------------------------
    // Rigidbody
    // -------------------------

    if (definition.HasRigidbody)
    {
        auto rigidbody =
            object->AddComponent<RigidbodyComponent>();

        rigidbody->SetMass(
            definition.Mass);

        rigidbody->SetUseGravity(
            definition.UseGravity);

        rigidbody->SetGravityScale(
            definition.GravityScale);

        rigidbody->SetKinematic(
            definition.Kinematic);

        rigidbody->SetVelocity(
            definition.InitialVelocity);
    }


    // -------------------------
    // Collider
    // -------------------------

    if (definition.HasCollider)
    {
        auto collider =
            object->AddComponent<BoxColliderComponent>();

        collider->SetSize(
            definition.ColliderSize.X,
            definition.ColliderSize.Y);

        collider->SetOffset(
            definition.ColliderOffset);

        collider->SetTrigger(
            definition.Trigger);

        collider->SetLayer(
            definition.Layer);
    }

    if (definition.HasDestroyOnCollision)
    {
        auto component =
            object->AddComponent<
            DestroyOnCollisionComponent>();

        component->SetDelay(
            definition.DestroyDelay);

        component->SetOnlyPlayer(
            definition.DestroyOnlyPlayer);
    }

    // -------------------------
// Damage
// -------------------------

    if (definition.HasDamage)
    {
        auto damage =
            object->AddComponent<
            DamageOnCollisionComponent>();

        damage->SetDamage(
            definition.Damage);
    }

    // -------------------------
// Health
// -------------------------

    if (definition.HasHealth)
    {
        auto health =
            object->AddComponent<HealthComponent>();

        health->SetMaxHealth(
            definition.MaxHealth);

        health->SetHealth(
            definition.Health);
    }

    // -------------------------
// Moving Platform
// -------------------------

    if (definition.HasMovingPlatform)
    {
        auto platform =
            object->AddComponent<
            MovingPlatformComponent>();

        platform->SetSpeed(
            definition.MovementSpeed);

        platform->SetLoop(
            definition.MovementLoop);

        for (const auto& point :
            definition.MovementPoints)
        {
            platform->AddPoint(point);
        }
    }
    // -------------------------
    // Player Controller
    // -------------------------

    if (definition.HasPlayerController)
    {
        auto controller =
            object->AddComponent<
            PlayerControllerComponent>();

        controller->SetMoveSpeed(
            definition.MoveSpeed);
    }
    // -------------------------
// Enemy
// -------------------------

    if (definition.HasEnemyController)
    {
        auto enemy =
            object->AddComponent<
            EnemyControllerComponent>();

        enemy->SetSpeed(
            definition.EnemySpeed);

        enemy->SetViewRadius(
            definition.EnemyViewRadius);

        for (const auto& point :
            definition.EnemyPoints)
        {
            enemy->AddPoint(point);
        }
    }

    return object;
}