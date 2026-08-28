#include "UIElement.h"

UIElement::UIElement()
{
    m_Position =
        Math::Vector2(
            0.0f,
            0.0f);

    m_Size =
        Math::Vector2(
            100.0f,
            50.0f);

    m_Visible = true;
    m_Enabled = true;
}

UIElement::~UIElement()
{
}

void UIElement::Update(float deltaTime)
{
}

void UIElement::Render(Renderer& renderer)
{
}

void UIElement::SetPosition(
    const Math::Vector2& position)
{
    m_Position = position;
}

const Math::Vector2&
UIElement::GetPosition() const
{
    return m_Position;
}

void UIElement::SetSize(
    const Math::Vector2& size)
{
    m_Size = size;
}

const Math::Vector2&
UIElement::GetSize() const
{
    return m_Size;
}

void UIElement::SetVisible(bool visible)
{
    m_Visible = visible;
}

bool UIElement::IsVisible() const
{
    return m_Visible;
}

void UIElement::SetEnabled(bool enabled)
{
    m_Enabled = enabled;
}

bool UIElement::IsEnabled() const
{
    return m_Enabled;
}

bool UIElement::ContainsPoint(
    const Math::Vector2& point) const
{
    return
        point.X >= m_Position.X &&
        point.X <= m_Position.X + m_Size.X &&
        point.Y >= m_Position.Y &&
        point.Y <= m_Position.Y + m_Size.Y;
}