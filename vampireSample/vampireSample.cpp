// vampireSample.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <map>
#pragma comment(lib, "gdiplus.lib")
#include <vector>
#include <string>
#include <stdlib.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "framework.h"
#include "vampireSample.h"
#include "global.h"

using namespace Gdiplus;
using namespace std;

ULONG_PTR gdiplusToken;  // Для инициализации GDI+


#define MAX_LOADSTRING 100

Hero bennet(0, 5, currentDirection_::state, { L"heroLeft.png", L"heroState.png", L"heroRight.png" }, 100.0f);

void InitMenu(int width, int height) {

    Image menuImage(LR"(MainMenu.png)");
    menu_image = menuImage.GetThumbnailImage(width, height, nullptr, nullptr);
    musicPath = L"menuMusic.wav";
    playButtonX1 = int(width * 0.43f);
    playButtonX2 = int(width * 0.58f);
    playButtonY1 = int(height * 0.47f);
    playButtonY2 = int(height * 0.58f);
    PlaySound(musicPath, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
    init = true;
}
void InitGame() {
    musicPath = L"gameMusic.wav";
    PlaySound(musicPath, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
    init = true;
}
void Clear() {
    PlaySound(NULL, NULL, 0);
}
void DrawMenu(Graphics& graphics) {
    if (menu_image)
        graphics.DrawImage(menu_image, 0, 0);
        
}
void DrawMap(Graphics& graphics) {
    Image mapImage(mm[bennet.currentMapID].mapImage);

    map_image = mapImage.GetThumbnailImage(2000, 2000, nullptr, nullptr);
    if (map_image) {
        graphics.DrawImage(map_image, (int)mm[bennet.currentMapID].posX, (int)mm[bennet.currentMapID].posY);
    }
}

bool mouseClickedInRect(float x1, float x2, float y1, float y2)
{
    GetCursorPos(&p);
    int mouseX = p.x;
    int mouseY = p.y;
    bool insideX = (mouseX >= x1 && mouseX <= x2);
    bool insideY = (mouseY >= y1 && mouseY <= y2);

    bool leftPressed = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

    return insideX && insideY && leftPressed;
}

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VAMPIRESAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VAMPIRESAMPLE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VAMPIRESAMPLE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_MAXIMIZE);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {
        SetTimer(hWnd, 1, 3, NULL);  // Увеличили частоту таймера
        break;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rect;
        GetClientRect(hWnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);
        SelectObject(hdcMem, hbmMem);

        Graphics graphics(hdcMem);
        graphics.Clear(Color::White);

        if (gameState == gameState_::MainMenu) {
            if (!init) {
                InitMenu(width, height);
            }
            DrawMenu(graphics);
            for (int i = playButtonX1; i < playButtonX2; i++) {
                SetPixel(hdc, i, playButtonY1, Color::Black);
                SetPixel(hdc, i, playButtonY2, Color::Black);
                
            }
        }
        if (gameState == gameState_::game) {
            if (!init) {
                InitGame();
            }
            DrawMap(graphics);
            bennet.drawHero(graphics, width, height);
        }


        BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
        DeleteObject(hbmMem);
        DeleteDC(hdcMem);
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_TIMER: {
        if (gameState == gameState_::game) {
            bennet.move();  // Движение обрабатывается в таймере
        }
        InvalidateRect(hWnd, nullptr, FALSE);
        break;
    }

    case WM_LBUTTONDOWN: {
        if (gameState == gameState_::MainMenu && mouseClickedInRect(playButtonX1, playButtonX2, playButtonY1, playButtonY2)) {
            
            gameState = gameState_::game;
            Clear();
            init = false;
        }
        break;
    }

    case WM_KEYDOWN: {
        // Движение убрано отсюда - теперь обрабатывается в таймере
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}