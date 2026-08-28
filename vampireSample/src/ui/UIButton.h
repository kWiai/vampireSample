#pragma once

#include "UIElement.h"

#include <windows.h>
#include <string>
#include <functional>

class UIButton : public UIElement
{
public:

    UIButton();
    ~UIButton() override;

    void Update(
        float deltaTime) override;

    void Render(
        Renderer& renderer) override;

    // -------------------------
    // Text
    // -------------------------

    void SetText(
        const std::wstring& text);

    const std::wstring&
        GetText() const;

    // -------------------------
    // Colors
    // -------------------------

    void SetNormalColor(
        BYTE r,
        BYTE g,
        BYTE b);

    void SetHoverColor(
        BYTE r,
        BYTE g,
        BYTE b);

    void SetPressedColor(
        BYTE r,
        BYTE g,
        BYTE b);

    void SetTextColor(
        BYTE r,
        BYTE g,
        BYTE b);

    // -------------------------
    // Click
    // -------------------------

    void SetOnClick(
        std::function<void()> callback);

    // -------------------------
    // State
    // -------------------------

    bool IsHovered() const;

    bool IsPressed() const;

private:

    void DrawText(
        Renderer& renderer);

private:

    std::wstring m_Text;

    BYTE m_NormalR;
    BYTE m_NormalG;
    BYTE m_NormalB;

    BYTE m_HoverR;
    BYTE m_HoverG;
    BYTE m_HoverB;

    BYTE m_PressedR;
    BYTE m_PressedG;
    BYTE m_PressedB;

    BYTE m_TextR;
    BYTE m_TextG;
    BYTE m_TextB;

    bool m_Hovered;
    bool m_Pressed;

    std::function<void()> m_OnClick;
};