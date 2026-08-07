#pragma once

#include "Vector2.h"

class GameObject;
class BoxColliderComponent;

struct RaycastHit
{
    bool Hit = false;

    GameObject* Object = nullptr;

    BoxColliderComponent* Collider = nullptr;

    Math::Vector2 Point;

    Math::Vector2 Normal;

    float Distance = 0.0f;
};