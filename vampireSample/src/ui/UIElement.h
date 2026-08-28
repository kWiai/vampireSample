#pragma once

#include "src/utilits/Vector2.h"

class Renderer;

class UIElement
{
public:

    UIElement();
    virtual ~UIElement();

    virtual void Update(float deltaTime);
    virtual void Render(Renderer& renderer);

    void SetPosition(
        const Math::Vector2& position);

    const Math::Vector2& GetPosition() const;

    void SetSize(
        const Math::Vector2& size);

    const Math::Vector2& GetSize() const;

    void SetVisible(bool visible);
    bool IsVisible() const;

    void SetEnabled(bool enabled);
    bool IsEnabled() const;

    bool ContainsPoint(
        const Math::Vector2& point) const;

protected:

    Math::Vector2 m_Position;
    Math::Vector2 m_Size;

    bool m_Visible;
    bool m_Enabled;
};