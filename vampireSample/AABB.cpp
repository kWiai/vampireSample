#include "AABB.h"
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