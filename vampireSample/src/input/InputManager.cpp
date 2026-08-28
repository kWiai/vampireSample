#include "InputManager.h"

bool InputManager::m_CurrentKeys[256] = {};
bool InputManager::m_PreviousKeys[256] = {};

HWND InputManager::m_Window = nullptr;


// -------------------------------------------------
// Initialize
// -------------------------------------------------

void InputManager::Initialize(HWND hwnd)
{
    m_Window = hwnd;
}


// -------------------------------------------------
// Update
// -------------------------------------------------

void InputManager::Update()
{
    // Предыдущее состояние
    for (int i = 0; i < 256; i++)
    {
        m_PreviousKeys[i] =
            m_CurrentKeys[i];
    }

    // Keyboard

    m_CurrentKeys['W'] =
        GetAsyncKeyState('W') & 0x8000;

    m_CurrentKeys['A'] =
        GetAsyncKeyState('A') & 0x8000;

    m_CurrentKeys['S'] =
        GetAsyncKeyState('S') & 0x8000;

    m_CurrentKeys['D'] =
        GetAsyncKeyState('D') & 0x8000;

    // Space

    m_CurrentKeys[VK_SPACE] =
        GetAsyncKeyState(VK_SPACE) & 0x8000;

    // Escape

    m_CurrentKeys[VK_ESCAPE] =
        GetAsyncKeyState(VK_ESCAPE) & 0x8000;

    // Mouse

    m_CurrentKeys[VK_LBUTTON] =
        GetAsyncKeyState(VK_LBUTTON) & 0x8000;

    m_CurrentKeys[VK_RBUTTON] =
        GetAsyncKeyState(VK_RBUTTON) & 0x8000;
}


// -------------------------------------------------
// GetKeyIndex
// -------------------------------------------------

int InputManager::GetKeyIndex(Key key)
{
    switch (key)
    {
    case Key::W:
        return 'W';

    case Key::A:
        return 'A';

    case Key::S:
        return 'S';

    case Key::D:
        return 'D';

    case Key::Space:
        return VK_SPACE;

    case Key::Escape:
        return VK_ESCAPE;

    case Key::MouseLeft:
        return VK_LBUTTON;

    case Key::MouseRight:
        return VK_RBUTTON;
    }

    return 0;
}


// -------------------------------------------------
// GetKeyState
// -------------------------------------------------

bool InputManager::GetKeyState(Key key)
{
    int index =
        GetKeyIndex(key);

    return m_CurrentKeys[index];
}


// -------------------------------------------------
// GetKey
// -------------------------------------------------

bool InputManager::GetKey(Key key)
{
    return GetKeyState(key);
}


// -------------------------------------------------
// GetKeyDown
// -------------------------------------------------

bool InputManager::GetKeyDown(Key key)
{
    int index =
        GetKeyIndex(key);

    return
        m_CurrentKeys[index] &&
        !m_PreviousKeys[index];
}


// -------------------------------------------------
// GetKeyUp
// -------------------------------------------------

bool InputManager::GetKeyUp(Key key)
{
    int index =
        GetKeyIndex(key);

    return
        !m_CurrentKeys[index] &&
        m_PreviousKeys[index];
}


// -------------------------------------------------
// GetMousePosition
// -------------------------------------------------

Math::Vector2 InputManager::GetMousePosition()
{
    if (m_Window == nullptr)
    {
        return Math::Vector2(
            0.0f,
            0.0f);
    }

    POINT point;

    if (!GetCursorPos(&point))
    {
        return Math::Vector2(
            0.0f,
            0.0f);
    }

    // Переводим экранные координаты
    // в координаты клиентской области окна

    if (!ScreenToClient(
        m_Window,
        &point))
    {
        return Math::Vector2(
            0.0f,
            0.0f);
    }

    return Math::Vector2(
        static_cast<float>(point.x),
        static_cast<float>(point.y));
}