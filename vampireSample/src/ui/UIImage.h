#pragma once

#include "UIElement.h"

#include <memory>

class Texture2D;
class Renderer;

class UIImage : public UIElement
{
public:

    UIImage();
    explicit UIImage(
        std::shared_ptr<Texture2D> texture);

    ~UIImage() override;

    void SetTexture(
        std::shared_ptr<Texture2D> texture);

    std::shared_ptr<Texture2D>
        GetTexture() const;

    void Render(
        Renderer& renderer) override;

private:

    std::shared_ptr<Texture2D> m_Texture;
};