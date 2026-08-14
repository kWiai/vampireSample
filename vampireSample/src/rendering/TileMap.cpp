#include "src/rendering/TileMap.h"

TileMap::TileMap()
{
    m_Width = 0;
    m_Height = 0;

}

TileMap::~TileMap()
{

}

void TileMap::Create(
    int width,
    int height)
{
    m_Width = width;
    m_Height = height;

    m_Tiles.clear();
    m_Tiles.resize(width * height);
}

int TileMap::GetWidth() const
{
    return m_Width;
}

int TileMap::GetHeight() const
{
    return m_Height;
}

Tile& TileMap::GetTile(
    int x,
    int y)
{
    return m_Tiles.at(GetIndex(x, y));
}

const Tile& TileMap::GetTile(
    int x,
    int y) const
{
    return m_Tiles.at(GetIndex(x, y));
}
bool TileMap::IsValidPosition(
    int x,
    int y) const
{
    return
        x >= 0 &&
        x < m_Width &&
        y >= 0 &&
        y < m_Height;
}

void TileMap::SetTile(
    int x,
    int y,
    int tileId)
{
    if (!IsValidPosition(x, y))
        return;

    GetTile(x, y).SetId(tileId);
}

int TileMap::GetIndex(
    int x,
    int y) const
{
    return y * m_Width + x;
}