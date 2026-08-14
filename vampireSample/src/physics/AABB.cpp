#include "src/physics/AABB.h"
#include <iostream>
using namespace Physics;

AABB::AABB()
{

}

AABB::AABB(
    const Math::Vector2& min,
    const Math::Vector2& max)
{
    Min = min;
    Max = max;
}

bool AABB::Intersects(
    const AABB& other) const
{
    return
        Max.X > other.Min.X &&
        Min.X < other.Max.X &&
        Max.Y > other.Min.Y &&
        Min.Y < other.Max.Y;
}
Math::Vector2 AABB::GetOverlap(
    const AABB& other) const
{
    float overlapX =
        std::min(Max.X, other.Max.X) -
        std::max(Min.X, other.Min.X);

    float overlapY =
        std::min(Max.Y, other.Max.Y) -
        std::max(Min.Y, other.Min.Y);

    return Math::Vector2(
        overlapX,
        overlapY);
}
bool AABB::Raycast(
    const Math::Vector2& origin,
    const Math::Vector2& direction,
    float maxDistance,
    float& distance,
    Math::Vector2& normal) const
{
    float tMin = 0.0f;
    float tMax = maxDistance;

    normal = Math::Vector2(0.0f, 0.0f);

    // X

    if (direction.X != 0.0f)
    {
        float tx1 = (Min.X - origin.X) / direction.X;
        float tx2 = (Max.X - origin.X) / direction.X;

        float txMin = std::min(tx1, tx2);
        float txMax = std::max(tx1, tx2);

        if (txMin > tMin)
        {
            tMin = txMin;

            normal =
                (tx1 < tx2)
                ? Math::Vector2(-1.0f, 0.0f)
                : Math::Vector2(1.0f, 0.0f);
        }

        tMax = std::min(tMax, txMax);

        if (tMin > tMax)
            return false;
    }
    else
    {
        if (origin.X < Min.X || origin.X > Max.X)
            return false;
    }

    // Y

    if (direction.Y != 0.0f)
    {
        float ty1 = (Min.Y - origin.Y) / direction.Y;
        float ty2 = (Max.Y - origin.Y) / direction.Y;

        float tyMin = std::min(ty1, ty2);
        float tyMax = std::max(ty1, ty2);

        if (tyMin > tMin)
        {
            tMin = tyMin;

            normal =
                (ty1 < ty2)
                ? Math::Vector2(0.0f, -1.0f)
                : Math::Vector2(0.0f, 1.0f);
        }

        tMax = std::min(tMax, tyMax);

        if (tMin > tMax)
            return false;
    }
    else
    {
        if (origin.Y < Min.Y || origin.Y > Max.Y)
            return false;
    }

    distance = tMin;

    return true;
}