#pragma once

#include <memory>
#include <string>

#include "src/core/Component.h"
#include "src/rendering/Sprite.h"

class Texture2D;
class Renderer;

class SpriteComponent : public Component
{
public:

    SpriteComponent();
    ~SpriteComponent() override;

    void Render(
        Renderer& renderer,
        const Camera& camera);

    // Работа со Sprite
    void SetSprite(const Sprite& sprite);

    Sprite& GetSprite();
    const Sprite& GetSprite() const;

    // Работа с текстурой
    void LoadTexture(const std::wstring& filePath);
    void SetTexture(std::shared_ptr<Texture2D> texture);
    std::shared_ptr<Texture2D> GetTexture() const;

    // Transform
    void SetSize(float width, float height);

    // Параметры отображения
    void SetScale(float scale);
    float GetScale() const;

    void SetRotation(float rotation);
    float GetRotation() const;

    void SetAlpha(float alpha);
    float GetAlpha() const;

    void SetFlipX(bool flip);
    bool IsFlipX() const;

    void SetFlipY(bool flip);
    bool IsFlipY() const;

    void SetLayer(int layer);
    int GetLayer() const;

private:

    Sprite m_Sprite;
};