#include "src/core/Window.h"

#include "src/utilits/Globals.h"

Window::Window()
{
    m_hWnd = nullptr;

    m_Width = WINDOW_WIDTH;
    m_Height = WINDOW_HEIGHT;
    m_WasResized = false;
}

Window::~Window()
{

}
bool Window::WasResized()
{
    if (!m_WasResized)
        return false;

    m_WasResized = false;

    return true;
}

bool Window::Create(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wc{};

    wc.cbSize = sizeof(WNDCLASSEX);

    wc.style = CS_HREDRAW | CS_VREDRAW;

    wc.lpfnWndProc = WindowProc;

    wc.hInstance = hInstance;

    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    wc.lpszClassName = L"GameWindow";

    RegisterClassEx(&wc);

    RECT rect =
    {
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    };

    AdjustWindowRect(
        &rect,
        WS_OVERLAPPEDWINDOW,
        FALSE
    );

    m_hWnd = CreateWindowEx(
        0,
        L"GameWindow",
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT,
        CW_USEDEFAULT,

        rect.right - rect.left,
        rect.bottom - rect.top,

        nullptr,
        nullptr,
        hInstance,
        this
    );

    if (m_hWnd == nullptr)
        return false;

    ShowWindow(m_hWnd, nCmdShow);

    UpdateWindow(m_hWnd);

    return true;
}

bool Window::ProcessMessages()
{
    MSG msg;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return false;

        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }

    return true;
}

HWND Window::GetHWND() const
{
    return m_hWnd;
}

int Window::GetWidth() const
{
    return m_Width;
}

int Window::GetHeight() const
{
    return m_Height;
}

LRESULT CALLBACK Window::WindowProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    Window* window = nullptr;

    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* createStruct =
            reinterpret_cast<CREATESTRUCT*>(
                lParam);

        window =
            static_cast<Window*>(
                createStruct->lpCreateParams);

        SetWindowLongPtr(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(
                window));
    }
    else
    {
        window =
            reinterpret_cast<Window*>(
                GetWindowLongPtr(
                    hwnd,
                    GWLP_USERDATA));
    }

    switch (msg)
    {
    case WM_SIZE:
    {
        if (window != nullptr)
        {
            window->m_Width =
                LOWORD(lParam);

            window->m_Height =
                HIWORD(lParam);

            window->m_WasResized =
                true;
        }

        return 0;
    }

    case WM_DESTROY:

        PostQuitMessage(0);

        return 0;
    }

    return DefWindowProc(
        hwnd,
        msg,
        wParam,
        lParam
    );
}