#pragma once

#include <vector>

#include "Tile.h"
#include "TileSet.h"

class TileMap
{
public:

    TileMap();
    ~TileMap();

    void Create(
        int width,
        int height);

    int GetWidth() const;
    int GetHeight() const;

    Tile& GetTile(int x, int y);
    const Tile& GetTile(int x, int y) const;
    bool IsValidPosition(
        int x,
        int y) const;

    bool IsSolid(
        int x,
        int y) const;

    void SetTile(
        int x,
        int y,
        int tileId);

    void SetSolid(
        int x,
        int y,
        bool solid);

private:

    int GetIndex(int x, int y) const;

private:

    int m_Width;
    int m_Height;

    std::vector<Tile> m_Tiles;
};