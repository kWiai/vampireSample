#pragma once

#include "Component.h"
#include "TileMap.h"

namespace Gdiplus { class Bitmap; }   // forward declaration

class Renderer;
class Camera;

class TileMapComponent : public Component
{
public:
    TileMapComponent();
    ~TileMapComponent() override;

    TileMap& GetTileMap();
    const TileMap& GetTileMap() const;
    void SetTileSet(TileSet* tileSet);
    TileSet* GetTileSet() const;

    void CacheMap();   // Создаёт кэш карты после загрузки

    void Render(Renderer& renderer, const Camera& camera) override;
    void RenderDebug(Renderer& renderer, const Camera& camera);

private:
    TileMap m_TileMap;
    TileSet* m_TileSet;
    Gdiplus::Bitmap* m_CachedMap = nullptr;
};