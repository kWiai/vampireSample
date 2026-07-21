#pragma once

#include <windows.h>

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

    static void Update();

    static bool GetKey(Key key);

    static bool GetKeyDown(Key key);

    static bool GetKeyUp(Key key);

private:

    static bool GetKeyState(Key key);

private:

    static bool m_CurrentKeys[256];
    static bool m_PreviousKeys[256];
};