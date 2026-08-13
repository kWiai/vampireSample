#include "CollisionMatrix.h"

bool CollisionMatrix::m_Matrix
[
    (int)CollisionLayer::COUNT
]
[
    (int)CollisionLayer::COUNT
];

void CollisionMatrix::Initialize()
{
    // По умолчанию запрещаем всё

    for (int i = 0; i < (int)CollisionLayer::COUNT; i++)
    {
        for (int j = 0; j < (int)CollisionLayer::COUNT; j++)
        {
            m_Matrix[i][j] = false;
        }
    }

    // ---------- PLAYER ----------

    m_Matrix[(int)CollisionLayer::Player]
        [(int)CollisionLayer::Wall] = true;

    m_Matrix[(int)CollisionLayer::Wall]
        [(int)CollisionLayer::Player] = true;

    m_Matrix[(int)CollisionLayer::Player]
        [(int)CollisionLayer::Enemy] = false;

    m_Matrix[(int)CollisionLayer::Enemy]
        [(int)CollisionLayer::Player] = true;

    // ---------- ENEMY ----------

    m_Matrix[(int)CollisionLayer::Enemy]
        [(int)CollisionLayer::Wall] = true;

    m_Matrix[(int)CollisionLayer::Wall]
        [(int)CollisionLayer::Enemy] = true;

    // Потом будем добавлять
    // Projectile
    // Loot
    // Trigger
}

bool CollisionMatrix::CanCollide(
    CollisionLayer a,
    CollisionLayer b)
{
    return
        m_Matrix[(int)a]
        [(int)b];
}