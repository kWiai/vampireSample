#include "SpatialHash.h"

#include "BoxColliderComponent.h"
#include "AABB.h"
#include "Render.h"
#include "Camera.h"

void SpatialHash::Clear()
{
    m_Cells.clear();
}
void SpatialHash::Insert(
    BoxColliderComponent* collider)
{
    Physics::AABB bounds =
        collider->GetBounds();

    int left =
        static_cast<int>(bounds.Min.X) / CellSize;

    int right =
        static_cast<int>(bounds.Max.X - 1) / CellSize;

    int top =
        static_cast<int>(bounds.Min.Y) / CellSize;

    int bottom =
        static_cast<int>(bounds.Max.Y - 1) / CellSize;

    for (int y = top; y <= bottom; y++)
    {
        for (int x = left; x <= right; x++)
        {
            Cell cell;

            cell.X = x;
            cell.Y = y;

            m_Cells[cell].push_back(collider);
        }
    }
}
void SpatialHash::Query(
    BoxColliderComponent* collider,
    std::vector<BoxColliderComponent*>& result)
{
    result.clear();

    Physics::AABB bounds =
        collider->GetBounds();

    int left =
        static_cast<int>(bounds.Min.X) / CellSize;

    int right =
        static_cast<int>(bounds.Max.X - 1) / CellSize;

    int top =
        static_cast<int>(bounds.Min.Y) / CellSize;

    int bottom =
        static_cast<int>(bounds.Max.Y - 1) / CellSize;

    for (int y = top; y <= bottom; y++)
    {
        for (int x = left; x <= right; x++)
        {
            Cell cell;

            cell.X = x;
            cell.Y = y;

            auto it =
                m_Cells.find(cell);

            if (it == m_Cells.end())
                continue;

            for (auto* other : it->second)
            {
                if (other == collider)
                    continue;

                if (std::find(
                    result.begin(),
                    result.end(),
                    other) == result.end())
                {
                    result.push_back(other);
                }
            }
        }
    }
}
void SpatialHash::DebugDraw(
    Renderer& renderer,
    const Camera& camera) const
{
    for (const auto& pair : m_Cells)
    {
        const Cell& cell =
            pair.first;

        renderer.DrawRectangle(
            cell.X * CellSize,
            cell.Y * CellSize,
            CellSize,
            CellSize,
            camera,
            0,
            120,
            255,
            1.0f);
    }
}