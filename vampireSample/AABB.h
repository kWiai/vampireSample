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

    public:

        Math::Vector2 Min;
        Math::Vector2 Max;
    };
}