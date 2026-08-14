#pragma once

#include "src/physics/CollisionLayer.h"

class CollisionMatrix
{
public:

    static void Initialize();

    static bool CanCollide(
        CollisionLayer a,
        CollisionLayer b);

private:

    static bool
        m_Matrix[
            (int)CollisionLayer::COUNT]
        [
            (int)CollisionLayer::COUNT];
};