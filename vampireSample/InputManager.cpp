#include "InputManager.h"

bool InputManager::m_CurrentKeys[256] = {};
bool InputManager::m_PreviousKeys[256] = {};

void InputManager::Update()
{
    for (int i = 0; i < 256; i++)
    {
        m_PreviousKeys[i] = m_CurrentKeys[i];
    }

    m_CurrentKeys['W'] = GetAsyncKeyState('W') & 0x8000;
    m_CurrentKeys['A'] = GetAsyncKeyState('A') & 0x8000;
    m_CurrentKeys['S'] = GetAsyncKeyState('S') & 0x8000;
    m_CurrentKeys['D'] = GetAsyncKeyState('D') & 0x8000;

    m_CurrentKeys[VK_SPACE] = GetAsyncKeyState(VK_SPACE) & 0x8000;
    m_CurrentKeys[VK_ESCAPE] = GetAsyncKeyState(VK_ESCAPE) & 0x8000;

    m_CurrentKeys[VK_LBUTTON] = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
    m_CurrentKeys[VK_RBUTTON] = GetAsyncKeyState(VK_RBUTTON) & 0x8000;
}
bool InputManager::GetKeyState(Key key)
{
    switch (key)
    {
    case Key::W:
        return m_CurrentKeys['W'];

    case Key::A:
        return m_CurrentKeys['A'];

    case Key::S:
        return m_CurrentKeys['S'];

    case Key::D:
        return m_CurrentKeys['D'];

    case Key::Space:
        return m_CurrentKeys[VK_SPACE];

    case Key::Escape:
        return m_CurrentKeys[VK_ESCAPE];

    case Key::MouseLeft:
        return m_CurrentKeys[VK_LBUTTON];

    case Key::MouseRight:
        return m_CurrentKeys[VK_RBUTTON];
    }

    return false;
}
bool InputManager::GetKey(Key key)
{
    return GetKeyState(key);
}

bool InputManager::GetKeyDown(Key key)
{
    bool current = GetKeyState(key);

    bool previous = false;

    switch (key)
    {
    case Key::W:
        previous = m_PreviousKeys['W'];
        break;

    case Key::A:
        previous = m_PreviousKeys['A'];
        break;

    case Key::S:
        previous = m_PreviousKeys['S'];
        break;

    case Key::D:
        previous = m_PreviousKeys['D'];
        break;

    case Key::Space:
        previous = m_PreviousKeys[VK_SPACE];
        break;

    case Key::Escape:
        previous = m_PreviousKeys[VK_ESCAPE];
        break;

    case Key::MouseLeft:
        previous = m_PreviousKeys[VK_LBUTTON];
        break;

    case Key::MouseRight:
        previous = m_PreviousKeys[VK_RBUTTON];
        break;
    }

    return current && !previous;
}

bool InputManager::GetKeyUp(Key key)
{
    bool current = GetKey(key);

    return !current && GetKeyDown(key) == false;
}