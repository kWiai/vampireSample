#pragma once

#include <windows.h>
#include <gdiplus.h>
#include "Sprite.h"
#include "Transform.h"
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
        const Transform& transform);

    Graphics* GetGraphics();

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
};