#pragma once

#include "Vector2.h"

class Transform
{
public:

    Transform();
    ~Transform();

public:

    Math::Vector2 Position;

    Math::Vector2 Size;

    Math::Vector2 Scale;

    float Rotation;
};