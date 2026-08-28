#include "UIButton.h"

#include "src/rendering/Render.h"
#include "src/input/InputManager.h"

#include <gdiplus.h>

using namespace Gdiplus;


// -------------------------------------------------
// Constructor
// -------------------------------------------------

UIButton::UIButton()
{
    m_Text = L"Button";

    // Normal
    m_NormalR = 70;
    m_NormalG = 70;
    m_NormalB = 70;

    // Hover
    m_HoverR = 100;
    m_HoverG = 100;
    m_HoverB = 100;

    // Pressed
    m_PressedR = 50;
    m_PressedG = 50;
    m_PressedB = 50;

    // Text
    m_TextR = 255;
    m_TextG = 255;
    m_TextB = 255;

    m_Hovered = false;
    m_Pressed = false;

    m_OnClick = nullptr;
}


// -------------------------------------------------
// Destructor
// -------------------------------------------------

UIButton::~UIButton()
{
}


// -------------------------------------------------
// Update
// -------------------------------------------------

void UIButton::Update(
    float deltaTime)
{
    Math::Vector2 mousePosition =
        InputManager::GetMousePosition();

    m_Hovered =
        ContainsPoint(mousePosition);

    // Если курсор не над кнопкой,
    // pressed должен быть false.

    if (!m_Hovered)
    {
        m_Pressed = false;
        return;
    }

    // Нажатие

    if (InputManager::GetKeyDown(
        Key::MouseLeft))
    {
        m_Pressed = true;
    }

    // Отпускание кнопки мыши

    if (InputManager::GetKeyUp(
        Key::MouseLeft))
    {
        if (m_Pressed)
        {
            if (m_OnClick)
            {
                m_OnClick();
            }
        }

        m_Pressed = false;
    }
}


// -------------------------------------------------
// Render
// -------------------------------------------------

void UIButton::Render(
    Renderer& renderer)
{
    if (!m_Visible)
        return;

    Graphics* graphics =
        renderer.GetGraphics();

    if (graphics == nullptr)
        return;

    BYTE r;
    BYTE g;
    BYTE b;

    // -------------------------
    // Select state color
    // -------------------------

    if (m_Pressed)
    {
        r = m_PressedR;
        g = m_PressedG;
        b = m_PressedB;
    }
    else if (m_Hovered)
    {
        r = m_HoverR;
        g = m_HoverG;
        b = m_HoverB;
    }
    else
    {
        r = m_NormalR;
        g = m_NormalG;
        b = m_NormalB;
    }

    // -------------------------
    // Background
    // -------------------------

    SolidBrush backgroundBrush(
        Color(
            255,
            r,
            g,
            b));

    graphics->FillRectangle(
        &backgroundBrush,
        m_Position.X,
        m_Position.Y,
        m_Size.X,
        m_Size.Y);

    // -------------------------
    // Border
    // -------------------------

    Pen borderPen(
        Color(
            255,
            255,
            255,
            255),
        2.0f);

    graphics->DrawRectangle(
        &borderPen,
        m_Position.X,
        m_Position.Y,
        m_Size.X,
        m_Size.Y);

    // -------------------------
    // Text
    // -------------------------

    DrawText(renderer);
}


// -------------------------------------------------
// DrawText
// -------------------------------------------------

void UIButton::DrawText(
    Renderer& renderer)
{
    Graphics* graphics =
        renderer.GetGraphics();

    if (graphics == nullptr)
        return;

    if (m_Text.empty())
        return;

    FontFamily fontFamily(L"Arial");

    Font font(
        &fontFamily,
        20.0f,
        FontStyleRegular,
        UnitPixel);

    SolidBrush textBrush(
        Color(
            255,
            m_TextR,
            m_TextG,
            m_TextB));

    StringFormat format;

    format.SetAlignment(
        StringAlignmentCenter);

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

void UIButton::SetText(
    const std::wstring& text)
{
    m_Text = text;
}

const std::wstring&
UIButton::GetText() const
{
    return m_Text;
}


// -------------------------------------------------
// Normal color
// -------------------------------------------------

void UIButton::SetNormalColor(
    BYTE r,
    BYTE g,
    BYTE b)
{
    m_NormalR = r;
    m_NormalG = g;
    m_NormalB = b;
}


// -------------------------------------------------
// Hover color
// -------------------------------------------------

void UIButton::SetHoverColor(
    BYTE r,
    BYTE g,
    BYTE b)
{
    m_HoverR = r;
    m_HoverG = g;
    m_HoverB = b;
}


// -------------------------------------------------
// Pressed color
// -------------------------------------------------

void UIButton::SetPressedColor(
    BYTE r,
    BYTE g,
    BYTE b)
{
    m_PressedR = r;
    m_PressedG = g;
    m_PressedB = b;
}


// -------------------------------------------------
// Text color
// -------------------------------------------------

void UIButton::SetTextColor(
    BYTE r,
    BYTE g,
    BYTE b)
{
    m_TextR = r;
    m_TextG = g;
    m_TextB = b;
}


// -------------------------------------------------
// OnClick
// -------------------------------------------------

void UIButton::SetOnClick(
    std::function<void()> callback)
{
    m_OnClick =
        std::move(callback);
}


// -------------------------------------------------
// IsHovered
// -------------------------------------------------

bool UIButton::IsHovered() const
{
    return m_Hovered;
}


// -------------------------------------------------
// IsPressed
// -------------------------------------------------

bool UIButton::IsPressed() const
{
    return m_Pressed;
}