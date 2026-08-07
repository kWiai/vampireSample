#pragma once

#include "Vector2.h"

namespace Physics
{
    class AABB
    {
    public:

        AABB();

        AABB(
            const Math::Vector2& min,
            const Math::Vector2& max);

        bool Intersects(
            const AABB& other) const;
        Math::Vector2 GetOverlap(const AABB& other) const;
        bool Raycast(
            const Math::Vector2& origin,
            const Math::Vector2& direction,
            float maxDistance,
            float& distance,
            Math::Vector2& normal) const;

    public:

        Math::Vector2 Min;
        Math::Vector2 Max;
    };
}