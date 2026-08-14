#include "HealthComponent.h"
#include "src/rendering/Render.h"
#include "src/rendering/Camera.h"
#include "src/core/GameObject.h"
#include "src/utilits/Vector2.h"
#include <gdiplus.h>

using namespace Gdiplus;

void HealthComponent::DrawHealthBar(Renderer& renderer, const Camera& camera, const Math::Vector2& offset, const Math::Vector2& size, bool isPlayer)
{
    if (IsDead() || m_MaxHealth <= 0.0f)
        return;

    float percent = m_Health / m_MaxHealth;
    if (percent < 0.0f) percent = 0.0f;
    if (percent > 1.0f) percent = 1.0f;

    Color fillColor;
    if (percent > 0.6f)      fillColor = Color(255, 0, 255, 0);   // зелёный
    else if (percent > 0.3f) fillColor = Color(255, 255, 255, 0); // жёлтый
    else                     fillColor = Color(255, 255, 0, 0);   // красный

    Color bgColor = Color(180, 0, 0, 0); // полупрозрачный чёрный

    Math::Vector2 pos;
    const Camera* drawCamera = &camera;
    Camera uiCamera; // камера без смещения (Identity)

    if (isPlayer) {
        drawCamera = &uiCamera;
        pos = offset; // offset задаётся в пикселях
    }
    else {
        pos = GetOwner()->GetTransform().Position + offset;
    }

    // Фон
    renderer.DrawFilledRectangle(
        pos.X, pos.Y,
        size.X, size.Y,
        *drawCamera,
        bgColor.GetR(), bgColor.GetG(), bgColor.GetB(), bgColor.GetA()
    );

    // Заполнение
    float fillWidth = size.X * percent;
    if (fillWidth > 0.0f) {
        renderer.DrawFilledRectangle(
            pos.X, pos.Y,
            fillWidth, size.Y,
            *drawCamera,
            fillColor.GetR(), fillColor.GetG(), fillColor.GetB(), fillColor.GetA()
        );
    }
}

HealthComponent::HealthComponent()
{
    m_MaxHealth = 100.0f;
    m_Health = 100.0f;
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::SetMaxHealth(float health)
{
    m_MaxHealth = health;

    if (m_MaxHealth < 0.0f)
        m_MaxHealth = 0.0f;

    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
}

float HealthComponent::GetMaxHealth() const
{
    return m_MaxHealth;
}

void HealthComponent::SetHealth(float health)
{
    m_Health = health;

    if (m_Health < 0.0f)
        m_Health = 0.0f;

    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
}

float HealthComponent::GetHealth() const
{
    return m_Health;
}

void HealthComponent::Heal(float amount)
{
    if (amount <= 0.0f)
        return;

    SetHealth(m_Health + amount);
}

void HealthComponent::TakeDamage(float amount)
{
    if (amount <= 0.0f)
        return;

    SetHealth(m_Health - amount);
}

bool HealthComponent::IsDead() const
{
    return m_Health <= 0.0f;
}