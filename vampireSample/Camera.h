#pragma once

#include "Vector2.h"

class Camera
{
public:

    Camera();
    ~Camera();

    // Update
    void Update(float deltaTime);

    // Position
    void SetPosition(const Math::Vector2& position);
    const Math::Vector2& GetPosition() const;

    void Move(const Math::Vector2& offset);

    // Zoom
    void SetZoom(float zoom);
    float GetZoom() const;

    // Rotation
    void SetRotation(float rotation);
    float GetRotation() const;

    // Viewport
    void SetViewportSize(float width, float height);
    Math::Vector2 GetViewportSize() const;
    Math::Vector2 GetCenter() const;

    // Coordinate conversion
    Math::Vector2 WorldToScreen(const Math::Vector2& worldPosition) const;
    Math::Vector2 ScreenToWorld(const Math::Vector2& screenPosition) const;

private:

    Math::Vector2 m_Position;

    Math::Vector2 m_ViewportSize;

    float m_Zoom;

    float m_Rotation;
};