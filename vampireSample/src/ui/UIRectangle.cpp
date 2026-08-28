#include "UIRectangle.h"

#include "src/rendering/Render.h"

UIRectangle::UIRectangle()
{
    m_R = 255;
    m_G = 255;
    m_B = 255;

    m_Alpha = 255;
}

UIRectangle::~UIRectangle()
{
}

void UIRectangle::Render(
    Renderer& renderer)
{
    if (!m_Visible)
        return;

    Graphics* graphics =
        renderer.GetGraphics();

    if (graphics == nullptr)
        return;

    SolidBrush brush(
        Color(
            m_Alpha,
            m_R,
            m_G,
            m_B));

    graphics->FillRectangle(
        &brush,
        m_Position.X,
        m_Position.Y,
        m_Size.X,
        m_Size.Y);
}

void UIRectangle::SetColor(
    BYTE r,
    BYTE g,
    BYTE b)
{
    m_R = r;
    m_G = g;
    m_B = b;
}

void UIRectangle::SetAlpha(
    BYTE alpha)
{
    m_Alpha = alpha;
}