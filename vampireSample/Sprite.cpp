#include "Sprite.h"

Sprite::Sprite()
{
    m_Texture = nullptr;
    m_SourceRect = Math::Rectangle();
    m_Scale = 1.0f;
    m_Rotation = 0.0f;

    m_Alpha = 1.0f;

    m_FlipX = false;
    m_FlipY = false;

    m_Layer = 0;
}

Sprite::Sprite(std::shared_ptr<Texture2D> texture)
    : Sprite()
{
    m_Texture = texture;
}

void Sprite::SetTexture(std::shared_ptr<Texture2D> texture)
{
    m_Texture = texture;
}

std::shared_ptr<Texture2D> Sprite::GetTexture() const
{
    return m_Texture;
}

void Sprite::SetScale(float scale)
{
    m_Scale = scale;
}

float Sprite::GetScale() const
{
    return m_Scale;
}

void Sprite::SetRotation(float rotation)
{
    m_Rotation = rotation;
}

float Sprite::GetRotation() const
{
    return m_Rotation;
}

void Sprite::SetAlpha(float alpha)
{
    m_Alpha = alpha;
}

float Sprite::GetAlpha() const
{
    return m_Alpha;
}

void Sprite::SetFlipX(bool flip)
{
    m_FlipX = flip;
}

bool Sprite::IsFlipX() const
{
    return m_FlipX;
}

void Sprite::SetFlipY(bool flip)
{
    m_FlipY = flip;
}

bool Sprite::IsFlipY() const
{
    return m_FlipY;
}

void Sprite::SetLayer(int layer)
{
    m_Layer = layer;
}

int Sprite::GetLayer() const
{
    return m_Layer;
}

void Sprite::SetSourceRect(const Math::Rectangle& rect)
{
    m_SourceRect = rect;
}

const Math::Rectangle& Sprite::GetSourceRect() const
{
    return m_SourceRect;
}