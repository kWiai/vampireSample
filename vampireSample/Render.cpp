#include "Render.h"

Renderer::Renderer()
{
    m_hWnd = nullptr;

    m_WindowDC = nullptr;
    m_BackDC = nullptr;

    m_BackBitmap = nullptr;
    m_OldBitmap = nullptr;

    m_Graphics = nullptr;

    m_GdiToken = 0;

    m_Width = 0;
    m_Height = 0;
}

Renderer::~Renderer()
{
    if (m_Graphics)
        delete m_Graphics;

    if (m_BackDC && m_OldBitmap)
        SelectObject(m_BackDC, m_OldBitmap);

    if (m_BackBitmap)
        DeleteObject(m_BackBitmap);

    if (m_BackDC)
        DeleteDC(m_BackDC);

    if (m_WindowDC)
        ReleaseDC(m_hWnd, m_WindowDC);

    GdiplusShutdown(m_GdiToken);
}

bool Renderer::Initialize(HWND hwnd, int width, int height)
{
    m_hWnd = hwnd;

    m_Width = width;
    m_Height = height;

    GdiplusStartupInput gdiplusStartupInput;

    GdiplusStartup(
        &m_GdiToken,
        &gdiplusStartupInput,
        nullptr
    );

    m_WindowDC = GetDC(hwnd);

    m_BackDC = CreateCompatibleDC(m_WindowDC);

    m_BackBitmap = CreateCompatibleBitmap(
        m_WindowDC,
        width,
        height
    );

    m_OldBitmap =
        (HBITMAP)SelectObject(
            m_BackDC,
            m_BackBitmap
        );

    m_Graphics = new Graphics(m_BackDC);

    return true;
}

void Renderer::BeginFrame()
{
    m_Graphics->Clear(Color(30, 30, 30));
}

void Renderer::EndFrame()
{
    BitBlt(
        m_WindowDC,
        0,
        0,
        m_Width,
        m_Height,
        m_BackDC,
        0,
        0,
        SRCCOPY
    );
}

Graphics* Renderer::GetGraphics()
{
    return m_Graphics;
}