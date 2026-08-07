#pragma once

#include <unordered_map>
#include <vector>
#include "Render.h"

class BoxColliderComponent;


struct Cell
{
    int X;
    int Y;

    bool operator==(const Cell& other) const
    {
        return
            X == other.X &&
            Y == other.Y;
    }
};

struct CellHasher
{
    size_t operator()(const Cell& cell) const
    {
        return
            std::hash<int>()(cell.X) ^
            (std::hash<int>()(cell.Y) << 1);
    }
};

class SpatialHash
{
public:

    void Clear();

    void Insert(BoxColliderComponent* collider);

    void Query(
        BoxColliderComponent* collider,
        std::vector<BoxColliderComponent*>& result);

    void DebugDraw(
        Renderer& renderer,
        const Camera& camera) const;

private:

    static constexpr int CellSize = 64;

    std::unordered_map<
        Cell,
        std::vector<BoxColliderComponent*>,
        CellHasher> m_Cells;
};