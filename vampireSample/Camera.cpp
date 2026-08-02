#include "Camera.h"
#include <iostream>

Camera::Camera()
{
    m_Position = Math::Vector2(0.0f, 0.0f);

    m_ViewportSize = Math::Vector2(1280.0f, 720.0f);

    m_Zoom = 1.0f;

    m_Rotation = 0.0f;
}

Camera::~Camera()
{

}

void Camera::SetPosition(const Math::Vector2& position)
{
    m_Position = position;
}

const Math::Vector2& Camera::GetPosition() const
{
    return m_Position;
}

void Camera::Move(const Math::Vector2& offset)
{
    m_Position += offset;
}

void Camera::SetZoom(float zoom)
{
    m_Zoom = zoom;
}

float Camera::GetZoom() const
{
    return m_Zoom;
}

void Camera::SetRotation(float rotation)
{
    m_Rotation = rotation;
}

float Camera::GetRotation() const
{
    return m_Rotation;
}

void Camera::SetViewportSize(float width, float height)
{
    m_ViewportSize = Math::Vector2(width, height);
}

Math::Vector2 Camera::GetViewportSize() const
{
    return m_ViewportSize;
}

Math::Vector2 Camera::GetCenter() const
{
    return Math::Vector2(
        m_ViewportSize.X * 0.5f,
        m_ViewportSize.Y * 0.5f
    );
}

Math::Vector2 Camera::WorldToScreen(const Math::Vector2& worldPosition) const
{
    Math::Vector2 screen;

    screen.X = (worldPosition.X - m_Position.X) * m_Zoom;
    screen.Y = (worldPosition.Y - m_Position.Y) * m_Zoom;
    screen.X = std::round(screen.X);
    screen.Y = std::round(screen.Y);

    return screen;
}

Math::Vector2 Camera::ScreenToWorld(const Math::Vector2& screenPosition) const
{
    Math::Vector2 world;

    world.X = screenPosition.X / m_Zoom + m_Position.X;
    world.Y = screenPosition.Y / m_Zoom + m_Position.Y;

    return world;
}