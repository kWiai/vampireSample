#include "src/rendering/TileSet.h"
#include <filesystem>
#include <iostream>
#include <string>
TileSet::TileSet()
{
    m_TileWidth = 0;
    m_TileHeight = 0;

    m_Columns = 0;
    m_Rows = 0;
}

TileSet::~TileSet()
{

}

bool TileSet::Load(const std::wstring& filePath, int tileWidth, int tileHeight)
{
    // Выводим путь в окно Output
    std::wstring msg = L"TileSet::Load: " + filePath + L"\n";
    OutputDebugStringW(msg.c_str());
    std::string narrowPath(filePath.begin(), filePath.end());
    if (!std::filesystem::exists(filePath))
    {
        std::string pathStr = "File not found: " + narrowPath + "\n";
        OutputDebugStringW(msg.c_str());
        return false;
    }
    

    m_Texture = std::make_shared<Texture2D>(filePath);
    if (!m_Texture->IsLoaded())
    {
        OutputDebugStringW(L"Texture2D failed to load!\n");
        return false;
    }

    m_TileWidth = tileWidth;
    m_TileHeight = tileHeight;

    Image* image =
        m_Texture->GetImage();

    m_Columns =
        image->GetWidth() / tileWidth;

    m_Rows =
        image->GetHeight() / tileHeight;

    BuildTiles();

    return true;
}

void TileSet::BuildTiles()
{
    m_Tiles.clear();

    for (int y = 0; y < m_Rows; y++)
    {
        for (int x = 0; x < m_Columns; x++)
        {
            TileInfo tile;

            tile.SourceRect =
                Math::Rectangle(
                    static_cast<float>(x * m_TileWidth),
                    static_cast<float>(y * m_TileHeight),
                    static_cast<float>(m_TileWidth),
                    static_cast<float>(m_TileHeight));

            tile.Solid = false;

            m_Tiles.push_back(tile);
        }
    }
}

std::shared_ptr<Texture2D> TileSet::GetTexture() const
{
    return m_Texture;
}

TileInfo& TileSet::GetTile(int id)
{
    return m_Tiles.at(id);
}

const TileInfo& TileSet::GetTile(int id) const
{
    return m_Tiles.at(id);
}

const Math::Rectangle& TileSet::GetSourceRect(int id) const
{
    return m_Tiles.at(id).SourceRect;
}

int TileSet::GetTileWidth() const
{
    return m_TileWidth;
}

int TileSet::GetTileHeight() const
{
    return m_TileHeight;
}

int TileSet::GetColumns() const
{
    return m_Columns;
}

int TileSet::GetRows() const
{
    return m_Rows;
}

int TileSet::GetTileCount() const
{
    return static_cast<int>(m_Tiles.size());
}