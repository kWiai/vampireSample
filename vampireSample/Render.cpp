#include "Render.h"
#include "Sprite.h"
#include "Transform.h"
#include "Camera.h"
#include <iostream>

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
void Renderer::DrawSprite(
    const Sprite& sprite,
    const Transform& transform,
    const Camera& camera)
{
    auto texture = sprite.GetTexture();

    if (!texture)
        return;

    if (!texture->IsLoaded())
        return;

    Image* image = texture->GetImage();

    if (!image)
        return;

    Math::Vector2 screenPosition =
        camera.WorldToScreen(
            transform.Position);

    RectF destination(
        screenPosition.X,
        screenPosition.Y,
        transform.Size.X,
        transform.Size.Y
    );

    m_Graphics->DrawImage(
        image,
        destination
    );
}
Graphics* Renderer::GetGraphics()
{
    return m_Graphics;
}

void Renderer::DrawGrid(const Camera& camera, int cellSize)
{
    Pen pen(Color(70, 70, 70));

    Math::Vector2 cameraPos = camera.GetPosition();

    int startX = static_cast<int>(cameraPos.X) / cellSize - 1;
    int endX = startX + 40;

    int startY = static_cast<int>(cameraPos.Y) / cellSize - 1;
    int endY = startY + 25;

    for (int x = startX; x <= endX; x++)
    {
        float worldX = x * cellSize;

        Math::Vector2 a =
            camera.WorldToScreen(Math::Vector2(worldX, cameraPos.Y));

        m_Graphics->DrawLine(
            &pen,
            (REAL)a.X,
            (REAL)0.0f,
            (REAL)a.X,
            (REAL)m_Height
        );
    }

    for (int y = startY; y <= endY; y++)
    {
        float worldY = y * cellSize;

        Math::Vector2 a =
            camera.WorldToScreen(Math::Vector2(cameraPos.X, worldY));

        m_Graphics->DrawLine(
            &pen,
            (REAL)0.0f,
            (REAL)a.Y,
            (REAL)m_Width,
            (REAL)a.Y
        );
    }
}