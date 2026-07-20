#pragma once

#include "Vector2.h"

class Transform
{
public:

    Transform();
    ~Transform();

public:

    Vector2 Position;

    Vector2 Size;

    Vector2 Scale;

    float Rotation;
};