#pragma once

#include <memory>
#include "Rectangle.h"
#include "Texture2D.h"

class Sprite
{
public:

    Sprite();
    explicit Sprite(std::shared_ptr<Texture2D> texture);

    void SetTexture(std::shared_ptr<Texture2D> texture);
    std::shared_ptr<Texture2D> GetTexture() const;

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

    void SetSourceRect(const Math::Rectangle& rect);

    const Math::Rectangle& GetSourceRect() const;

private:

    std::shared_ptr<Texture2D> m_Texture;

    Math::Rectangle m_SourceRect;

    float m_Scale;
    float m_Rotation;

    float m_Alpha;

    bool m_FlipX;
    bool m_FlipY;

    int m_Layer;
};