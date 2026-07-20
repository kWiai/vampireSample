#pragma once

#include "Component.h"
#include "Sprite.h"

class Renderer;

class SpriteComponent : public Component
{
public:

    SpriteComponent();
    ~SpriteComponent() override;

    void SetSprite(const Sprite& sprite);

    Sprite& GetSprite();
    const Sprite& GetSprite() const;

    void Render(Renderer& renderer) override;

private:

    Sprite m_Sprite;
};