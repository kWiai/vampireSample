#include "UIText.h"

#include "src/rendering/Render.h"

#include <gdiplus.h>

using namespace Gdiplus;

// -------------------------------------------------
// Constructor
// -------------------------------------------------

UIText::UIText()
{
    m_Text = L"Text";

    m_FontSize = 20.0f;

    m_R = 255;
    m_G = 255;
    m_B = 255;

    m_Centered = false;
}

// -------------------------------------------------
// Destructor
// -------------------------------------------------

UIText::~UIText()
{
}

// -------------------------------------------------
// Render
// -------------------------------------------------

void UIText::Render(
    Renderer& renderer)
{
    if (!m_Visible)
        return;

    if (m_Text.empty())
        return;

    Graphics* graphics =
        renderer.GetGraphics();

    if (graphics == nullptr)
        return;

    FontFamily fontFamily(L"Arial");

    Font font(
        &fontFamily,
        m_FontSize,
        FontStyleRegular,
        UnitPixel);

    SolidBrush textBrush(
        Color(
            255,
            m_R,
            m_G,
            m_B));

    StringFormat format;

    // Горизонтальное выравнивание
    if (m_Centered)
    {
        format.SetAlignment(
            StringAlignmentCenter);
    }
    else
    {
        format.SetAlignment(
            StringAlignmentNear);
    }

    // Вертикальное выравнивание
    format.SetLineAlignment(
        StringAlignmentCenter);

    RectF rect(
        m_Position.X,
        m_Position.Y,
        m_Size.X,
        m_Size.Y);

    graphics->DrawString(
        m_Text.c_str(),
        -1,
        &font,
        rect,
        &format,
        &textBrush);
}

// -------------------------------------------------
// Text
// -------------------------------------------------

void UIText::SetText(
    const std::wstring& text)
{
    m_Text = text;
}

const std::wstring&
UIText::GetText() const
{
    return m_Text;
}

// -------------------------------------------------
// Font size
// -------------------------------------------------

void UIText::SetFontSize(
    float size)
{
    if (size > 0.0f)
        m_FontSize = size;
}

float UIText::GetFontSize() const
{
    return m_FontSize;
}

// -------------------------------------------------
// Color
// -------------------------------------------------

void UIText::SetColor(
    BYTE r,
    BYTE g,
    BYTE b)
{
    m_R = r;
    m_G = g;
    m_B = b;
}

// -------------------------------------------------
// Alignment
// -------------------------------------------------

void UIText::SetCentered(
    bool centered)
{
    m_Centered = centered;
}