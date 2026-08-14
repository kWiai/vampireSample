#include "SpriteComponent.h"

#include "src/core/GameObject.h"
#include "src/rendering/Render.h"
#include "src/utilits/ResourceManager.h"
#include "src/rendering/Texture2D.h"

SpriteComponent::SpriteComponent()
{

}

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::SetSprite(const Sprite& sprite)
{
    m_Sprite = sprite;
}

Sprite& SpriteComponent::GetSprite()
{
    return m_Sprite;
}

const Sprite& SpriteComponent::GetSprite() const
{
    return m_Sprite;
}

void SpriteComponent::Render(Renderer& renderer, const Camera& camera)
{
    if (GetOwner() == nullptr)
        return;

    renderer.DrawSprite(
        m_Sprite,
        GetOwner()->GetTransform(),
        camera);
}

void SpriteComponent::LoadTexture(const std::wstring& filePath)
{
    m_Sprite.SetTexture(
        ResourceManager::LoadTexture(filePath));
}

void SpriteComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
    m_Sprite.SetTexture(texture);
}

std::shared_ptr<Texture2D> SpriteComponent::GetTexture() const
{
    return m_Sprite.GetTexture();
}

void SpriteComponent::SetSize(float width, float height)
{
    GetTransform().Size =
        Math::Vector2(width, height);
}

void SpriteComponent::SetScale(float scale)
{
    m_Sprite.SetScale(scale);
}

float SpriteComponent::GetScale() const
{
    return m_Sprite.GetScale();
}

void SpriteComponent::SetRotation(float rotation)
{
    m_Sprite.SetRotation(rotation);
}

float SpriteComponent::GetRotation() const
{
    return m_Sprite.GetRotation();
}

void SpriteComponent::SetAlpha(float alpha)
{
    m_Sprite.SetAlpha(alpha);
}

float SpriteComponent::GetAlpha() const
{
    return m_Sprite.GetAlpha();
}

void SpriteComponent::SetFlipX(bool flip)
{
    m_Sprite.SetFlipX(flip);
}

bool SpriteComponent::IsFlipX() const
{
    return m_Sprite.IsFlipX();
}

void SpriteComponent::SetFlipY(bool flip)
{
    m_Sprite.SetFlipY(flip);
}

bool SpriteComponent::IsFlipY() const
{
    return m_Sprite.IsFlipY();
}

void SpriteComponent::SetLayer(int layer)
{
    m_Sprite.SetLayer(layer);
}

int SpriteComponent::GetLayer() const
{
    return m_Sprite.GetLayer();
}