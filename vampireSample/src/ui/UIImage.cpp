#include "UIImage.h"

#include "src/rendering/Render.h"
#include "src/rendering/Texture2D.h"

UIImage::UIImage()
{
    m_Texture = nullptr;
}

UIImage::UIImage(
    std::shared_ptr<Texture2D> texture)
{
    m_Texture = texture;
}

UIImage::~UIImage()
{
}

void UIImage::SetTexture(
    std::shared_ptr<Texture2D> texture)
{
    m_Texture = texture;
}

std::shared_ptr<Texture2D>
UIImage::GetTexture() const
{
    return m_Texture;
}

void UIImage::Render(
    Renderer& renderer)
{
    if (!m_Visible)
        return;

    if (!m_Texture)
        return;

    if (!m_Texture->IsLoaded())
        return;

    Graphics* graphics =
        renderer.GetGraphics();

    if (graphics == nullptr)
        return;

    Image* image =
        m_Texture->GetImage();

    if (image == nullptr)
        return;

    graphics->DrawImage(
        image,
        m_Position.X,
        m_Position.Y,
        m_Size.X,
        m_Size.Y);
}