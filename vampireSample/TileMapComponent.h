#pragma once

#include "Component.h"
#include "TileMap.h"

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

    void Render(
        Renderer& renderer,
        const Camera& camera) override;

private:

    TileMap m_TileMap;

    TileSet* m_TileSet;
};