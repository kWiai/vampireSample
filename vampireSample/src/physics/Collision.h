#pragma once

#include "src/utilits/Vector2.h"

class GameObject;

struct Collision
{
    GameObject* Self;
    GameObject* Other;

    Math::Vector2 Normal;

    float Depth;

    bool operator==(const Collision& other) const
    {
        return
            Self == other.Self &&
            Other == other.Other;
    }
};
