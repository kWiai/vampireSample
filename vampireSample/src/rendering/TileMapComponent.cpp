#include "src/rendering/TileMapComponent.h"
#include "Render.h"
#include "Camera.h"
#include "TileSet.h"
#include <gdiplus.h>

TileMapComponent::TileMapComponent()
    : m_TileSet(nullptr), m_CachedMap(nullptr)
{
}

TileMapComponent::~TileMapComponent()
{
    if (m_CachedMap)
        delete m_CachedMap;
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

// Кэширование всей карты в один битмап
void TileMapComponent::CacheMap()
{
    if (!m_TileSet)
        return;

    const int tileW = m_TileSet->GetTileWidth();
    const int tileH = m_TileSet->GetTileHeight();
    const int mapW = m_TileMap.GetWidth();
    const int mapH = m_TileMap.GetHeight();

    if (m_CachedMap)
        delete m_CachedMap;

    m_CachedMap = new Gdiplus::Bitmap(mapW * tileW, mapH * tileH, PixelFormat32bppARGB);
    Gdiplus::Graphics g(m_CachedMap);
    g.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

    Gdiplus::Image* atlas = m_TileSet->GetTexture()->GetImage();

    for (int y = 0; y < mapH; ++y)
    {
        for (int x = 0; x < mapW; ++x)
        {
            const Tile& tile = m_TileMap.GetTile(x, y);
            if (tile.GetId() < 0) continue;

            const Math::Rectangle& src = m_TileSet->GetSourceRect(tile.GetId());

            // Прямоугольник назначения на кэше
            Gdiplus::RectF destRect(
                static_cast<REAL>(x * tileW),
                static_cast<REAL>(y * tileH),
                static_cast<REAL>(tileW),
                static_cast<REAL>(tileH)
            );

            g.DrawImage(atlas, destRect,
                src.x, src.y, src.width, src.height,
                Gdiplus::UnitPixel);
        }
    }
}

// Быстрый рендер одним DrawImage
void TileMapComponent::Render(Renderer& renderer, const Camera& camera)
{
    if (!m_CachedMap) return;

    Math::Vector2 camPos = camera.GetPosition();
    Math::Vector2 viewSize = camera.GetViewportSize();

    float srcX = camPos.X;
    float srcY = camPos.Y;
    float srcW = viewSize.X;
    float srcH = viewSize.Y;

    Gdiplus::Graphics* g = renderer.GetGraphics();
    if (!g) return;

    // Целевой прямоугольник – весь экран
    Gdiplus::RectF destRect(0.0f, 0.0f, viewSize.X, viewSize.Y);

    // Рисуем видимую часть кэша
    g->DrawImage(m_CachedMap, destRect,
        srcX, srcY, srcW, srcH,
        Gdiplus::UnitPixel);
}

// Отладочный рендер (можно отключить)
void TileMapComponent::RenderDebug(Renderer& renderer, const Camera& camera)
{
    if (m_TileSet == nullptr)
        return;

    const int w = m_TileSet->GetTileWidth();
    const int h = m_TileSet->GetTileHeight();

    for (int y = 0; y < m_TileMap.GetHeight(); y++)
    {
        for (int x = 0; x < m_TileMap.GetWidth(); x++)
        {
            const Tile& tile = m_TileMap.GetTile(x, y);
            const TileInfo& info = m_TileSet->GetTile(tile.GetId());
            if (!info.Solid)
                continue;

            renderer.DrawFilledRectangle(x * w, y * h, w, h, camera, 255, 0, 0, 70);
            renderer.DrawRectangle(x * w, y * h, w, h, camera, 255, 0, 0);
        }
    }
}