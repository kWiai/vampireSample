#pragma once

#include "UIElement.h"

#include <windows.h>

class UIRectangle : public UIElement
{
public:

    UIRectangle();
    ~UIRectangle() override;

    void Render(Renderer& renderer) override;

    void SetColor(
        BYTE r,
        BYTE g,
        BYTE b);

    void SetAlpha(
        BYTE alpha);

private:

    BYTE m_R;
    BYTE m_G;
    BYTE m_B;
    BYTE m_Alpha;
};