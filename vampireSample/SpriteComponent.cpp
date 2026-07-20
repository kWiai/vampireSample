#include "SpriteComponent.h"

#include "GameObject.h"
#include "Render.h"

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

void SpriteComponent::Render(Renderer& renderer)
{
    if (GetOwner() == nullptr)
        return;

    renderer.DrawSprite(
        m_Sprite,
        GetOwner()->GetTransform()
    );
}