#pragma once

#include <windows.h>
#include <gdiplus.h>

#include "Sprite.h"
#include "Transform.h"
#include "Camera.h"
#include "TileSet.h"
#include "Rectangle.h"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

class Renderer
{
public:

    Renderer();
    ~Renderer();

    bool Initialize(HWND hwnd, int width, int height);

    void BeginFrame();
    void EndFrame();

    void DrawSprite(
        const Sprite& sprite,
        const Transform& transform,
        const Camera& camera);

    void DrawTile(
        const TileSet& tileSet,
        int tileId,
        int tileX,
        int tileY,
        const Camera& camera);

    void DrawGrid(
        const Camera& camera,
        int cellSize = 32);

    void DrawRectangle(
        float x,
        float y,
        float width,
        float height,
        const Camera& camera,
        BYTE r = 0,
        BYTE g = 255,
        BYTE b = 0,
        float thickness = 2.0f);

    void DrawLine(
        float x1,
        float y1,
        float x2,
        float y2,
        const Camera& camera,
        BYTE r = 255,
        BYTE g = 255,
        BYTE b = 255,
        float thickness = 2.0f);

    void DrawFilledRectangle(
        float x,
        float y,
        float width,
        float height,
        const Camera& camera,
        BYTE r,
        BYTE g,
        BYTE b,
        BYTE alpha = 80);

    Graphics* GetGraphics();

    void SetShowColliders(bool value);


    bool IsShowingColliders() const;

private:

    void DrawTextureRegion(
        Image* image,
        const Math::Rectangle& source,
        const RectF& destination);

private:

    HWND m_hWnd;

    HDC m_WindowDC;
    HDC m_BackDC;

    HBITMAP m_BackBitmap;
    HBITMAP m_OldBitmap;

    Graphics* m_Graphics;

    ULONG_PTR m_GdiToken;

    int m_Width;
    int m_Height;
    bool m_ShowColliders;
};