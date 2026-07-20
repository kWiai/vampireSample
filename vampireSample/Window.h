#pragma once

#include <windows.h>

class Window
{
public:
    Window();
    ~Window();

    bool Create(HINSTANCE hInstance, int nCmdShow);

    bool ProcessMessages();

    HWND GetHWND() const;

    int GetWidth() const;
    int GetHeight() const;

private:

    HWND m_hWnd;

    int m_Width;
    int m_Height;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
    );
};