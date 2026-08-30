#pragma once

#include "UIElement.h"

#include <windows.h>
#include <string>

class Renderer;

class UIText : public UIElement
{
public:

    UIText();
    ~UIText() override;

    void Render(Renderer& renderer) override;

    // -------------------------
    // Text
    // -------------------------

    void SetText(
        const std::wstring& text);

    const std::wstring&
        GetText() const;

    // -------------------------
    // Font
    // -------------------------

    void SetFontSize(
        float size);

    float GetFontSize() const;

    // -------------------------
    // Color
    // -------------------------

    void SetColor(
        BYTE r,
        BYTE g,
        BYTE b);

    // -------------------------
    // Alignment
    // -------------------------

    void SetCentered(
        bool centered);

private:

    std::wstring m_Text;

    float m_FontSize;

    BYTE m_R;
    BYTE m_G;
    BYTE m_B;

    bool m_Centered;
};