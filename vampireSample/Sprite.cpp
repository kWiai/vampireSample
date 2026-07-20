#include "Sprite.h"

#include "Render.h"
#include "Texture2D.h"

Sprite::Sprite()
{

}

void Sprite::SetTexture(std::shared_ptr<Texture2D> texture)
{
    m_Texture = texture;
}

void Sprite::Draw(
    Renderer& renderer,
    float x,
    float y,
    float width,
    float height)
{
    if (!m_Texture)
        return;

    Graphics* graphics = renderer.GetGraphics();

    graphics->DrawImage(
        m_Texture->GetImage(),
        x,
        y,
        width,
        height);
}