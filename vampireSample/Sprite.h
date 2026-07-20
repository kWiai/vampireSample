#pragma once

#include <memory>

class Renderer;
class Texture2D;

class Sprite
{
public:

    Sprite();

    void SetTexture(std::shared_ptr<Texture2D> texture);

    void Draw(
        Renderer& renderer,
        float x,
        float y,
        float width,
        float height);

private:

    std::shared_ptr<Texture2D> m_Texture;
};