#include "TileMapComponent.h"

#include "Render.h"
#include "Camera.h"

TileMapComponent::TileMapComponent()
{
    m_TileSet = nullptr;
}

TileMapComponent::~TileMapComponent()
{

}

void TileMapComponent::SetTileSet(TileSet* tileSet)
{
    m_TileSet = tileSet;
}

TileSet* TileMapComponent::GetTileSet() const
{
    return m_TileSet;
}

TileMap& TileMapComponent::GetTileMap()
{
    return m_TileMap;
}

const TileMap& TileMapComponent::GetTileMap() const
{
    return m_TileMap;
}

void TileMapComponent::Render(
    Renderer& renderer,
    const Camera& camera)
{
    if (m_TileSet == nullptr)
        return;

    for (int y = 0; y < m_TileMap.GetHeight(); y++)
    {
        for (int x = 0; x < m_TileMap.GetWidth(); x++)
        {
            const Tile& tile =
                m_TileMap.GetTile(x, y);

            if (tile.GetId() < 0)
                continue;

            renderer.DrawTile(
                *m_TileSet,
                tile.GetId(),
                x,
                y,
                camera);
        }
    }
}