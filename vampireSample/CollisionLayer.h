#pragma once

enum class CollisionLayer
{
    Default = 0,

    Player,
    Enemy,
    Wall,
    Projectile,
    Trigger,
    Loot,

    COUNT
};