#pragma once

#include <windows.h>

#include "Window.h"
#include "Render.h"
#include "Time.h"
#include "Game.h"

class Application
{
public:

    Application();
    ~Application();

    int Run(HINSTANCE hInstance, int nCmdShow);

private:

    void Update();
    void RenderFrame();

private:

    Window m_Window;
    Renderer m_Renderer;
    Game m_Game;

    bool m_IsRunning;
};