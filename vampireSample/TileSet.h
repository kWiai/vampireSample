#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Texture2D.h"
#include "Rectangle.h"

struct TileInfo
{
    Math::Rectangle SourceRect;

    bool Solid = false;
};

class TileSet
{
public:

    TileSet();
    ~TileSet();

    bool Load(
        const std::wstring& filePath,
        int tileWidth,
        int tileHeight);

    std::shared_ptr<Texture2D> GetTexture() const;

    const TileInfo& GetTile(int id) const;

    int GetTileWidth() const;
    int GetTileHeight() const;

    int GetColumns() const;
    int GetRows() const;

    int GetTileCount() const;
    const Math::Rectangle& GetSourceRect(int id) const;

private:

    void BuildTiles();

private:

    std::shared_ptr<Texture2D> m_Texture;

    std::vector<TileInfo> m_Tiles;

    int m_TileWidth;
    int m_TileHeight;

    int m_Columns;
    int m_Rows;
};