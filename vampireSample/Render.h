#pragma once

#include <windows.h>
#include <gdiplus.h>

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