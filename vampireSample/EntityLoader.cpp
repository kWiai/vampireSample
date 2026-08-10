#include "EntityLoader.h"

#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool EntityLoader::Load(
    const std::string& filePath,
    EntityDefinition& definition)
{
    std::ifstream file(filePath);

    if (!file.is_open())
        return false;

    json data;

    try
    {
        file >> data;
    }
    catch (...)
    {
        return false;
    }


    // -------------------------
    // Name
    // -------------------------

    if (data.contains("Name"))
    {
        definition.Name =
            data["Name"].get<std::string>();
    }


    // -------------------------
    // Transform
    // -------------------------

    if (data.contains("Transform"))
    {
        const auto& transform =
            data["Transform"];

        if (transform.contains("Position"))
        {
            definition.Position =
                Math::Vector2(
                    transform["Position"][0].get<float>(),
                    transform["Position"][1].get<float>());
        }

        if (transform.contains("Size"))
        {
            definition.Size =
                Math::Vector2(
                    transform["Size"][0].get<float>(),
                    transform["Size"][1].get<float>());
        }
    }


    // -------------------------
    // Sprite
    // -------------------------

    if (data.contains("Sprite"))
    {
        const auto& sprite =
            data["Sprite"];

        definition.HasSprite =
            sprite.value("Enabled", false);

        if (sprite.contains("Texture"))
        {
            std::string texture =
                sprite["Texture"].get<std::string>();

            definition.Texture =
                std::wstring(
                    texture.begin(),
                    texture.end());
        }
    }


    // -------------------------
    // Animation
    // -------------------------

    if (data.contains("Animation"))
    {
        const auto& animation =
            data["Animation"];

        definition.HasAnimation =
            animation.value(
                "Enabled",
                false);


        // ---------- Idle ----------

        if (animation.contains("Idle"))
        {
            const auto& idle =
                animation["Idle"];

            definition.Idle.HasAnimation =
                idle.value(
                    "Enabled",
                    false);

            if (idle.contains("Texture"))
            {
                std::string texture =
                    idle["Texture"]
                    .get<std::string>();

                definition.Idle.Texture =
                    std::wstring(
                        texture.begin(),
                        texture.end());
            }

            definition.Idle.FrameCount =
                idle.value(
                    "FrameCount",
                    1);

            definition.Idle.FrameWidth =
                idle.value(
                    "FrameWidth",
                    0);

            definition.Idle.FrameHeight =
                idle.value(
                    "FrameHeight",
                    0);

            definition.Idle.FrameDuration =
                idle.value(
                    "FrameDuration",
                    0.1f);

            definition.Idle.Loop =
                idle.value(
                    "Loop",
                    true);
        }


        // ---------- Walk ----------

        if (animation.contains("Walk"))
        {
            const auto& walk =
                animation["Walk"];

            definition.Walk.HasAnimation =
                walk.value(
                    "Enabled",
                    false);

            if (walk.contains("Texture"))
            {
                std::string texture =
                    walk["Texture"]
                    .get<std::string>();

                definition.Walk.Texture =
                    std::wstring(
                        texture.begin(),
                        texture.end());
            }

            definition.Walk.FrameCount =
                walk.value(
                    "FrameCount",
                    1);

            definition.Walk.FrameWidth =
                walk.value(
                    "FrameWidth",
                    0);

            definition.Walk.FrameHeight =
                walk.value(
                    "FrameHeight",
                    0);

            definition.Walk.FrameDuration =
                walk.value(
                    "FrameDuration",
                    0.1f);

            definition.Walk.Loop =
                walk.value(
                    "Loop",
                    true);
        }
    }


    // -------------------------
    // Rigidbody
    // -------------------------

    if (data.contains("Rigidbody"))
    {
        const auto& rigidbody =
            data["Rigidbody"];

        definition.HasRigidbody =
            rigidbody.value(
                "Enabled",
                false);

        definition.UseGravity =
            rigidbody.value(
                "Gravity",
                false);

        definition.GravityScale =
            rigidbody.value(
                "GravityScale",
                1.0f);

        definition.Kinematic =
            rigidbody.value(
                "Kinematic",
                false);
    }


    // -------------------------
    // Collider
    // -------------------------

    if (data.contains("Collider"))
    {
        const auto& collider =
            data["Collider"];

        definition.HasCollider =
            collider.value(
                "Enabled",
                false);

        if (collider.contains("Size"))
        {
            definition.ColliderSize =
                Math::Vector2(
                    collider["Size"][0].get<float>(),
                    collider["Size"][1].get<float>());
        }

        if (collider.contains("Offset"))
        {
            definition.ColliderOffset =
                Math::Vector2(
                    collider["Offset"][0].get<float>(),
                    collider["Offset"][1].get<float>());
        }

        definition.Trigger =
            collider.value(
                "Trigger",
                false);

        if (collider.contains("Layer"))
        {
            std::string layer =
                collider["Layer"]
                .get<std::string>();

            if (layer == "Player")
            {
                definition.Layer =
                    CollisionLayer::Player;
            }
            else if(layer == "Wall") {
                
                definition.Layer =
                    CollisionLayer::Wall;
                
            }
            else if (layer == "Enemy") {

                definition.Layer =
                    CollisionLayer::Enemy;

            }
            else
            {
                definition.Layer =
                    CollisionLayer::Default;
            }
        }
    }

    // -------------------------
// Damage
// -------------------------

    if (data.contains("Damage"))
    {
        const auto& damage =
            data["Damage"];

        definition.HasDamage =
            damage.value(
                "Enabled",
                false);

        definition.Damage =
            damage.value(
                "Amount",
                0.0f);
    }

    // -------------------------
// Health
// -------------------------

    if (data.contains("Health"))
    {
        const auto& health =
            data["Health"];

        definition.HasHealth =
            health.value(
                "Enabled",
                false);

        definition.MaxHealth =
            health.value(
                "MaxHealth",
                100.0f);

        definition.Health =
            health.value(
                "Health",
                definition.MaxHealth);
    }

    // -------------------------
    // Player Controller
    // -------------------------

    if (data.contains("PlayerController"))
    {
        const auto& controller =
            data["PlayerController"];

        definition.HasPlayerController =
            controller.value(
                "Enabled",
                false);

        definition.MoveSpeed =
            controller.value(
                "MoveSpeed",
                300.0f);
    }


    return true;
}