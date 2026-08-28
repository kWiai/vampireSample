#pragma once

#include <windows.h>

#include "src/utilits/Vector2.h"

enum class Key
{
    W,
    A,
    S,
    D,

    Space,

    Escape,

    MouseLeft,
    MouseRight
};

class InputManager
{
public:

    // Инициализация окна,
    // относительно которого считаются координаты мыши
    static void Initialize(HWND hwnd);

    static void Update();

    static bool GetKey(Key key);

    static bool GetKeyDown(Key key);

    static bool GetKeyUp(Key key);

    static Math::Vector2 GetMousePosition();

private:

    static bool GetKeyState(Key key);

    static int GetKeyIndex(Key key);

private:

    static bool m_CurrentKeys[256];
    static bool m_PreviousKeys[256];

    static HWND m_Window;
};