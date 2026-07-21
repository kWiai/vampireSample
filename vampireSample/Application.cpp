#include "Application.h"
#include "InputManager.h"
#include <gdiplus.h>

using namespace Gdiplus;

Application::Application()
{
    m_IsRunning = true;
}

Application::~Application()
{

}

int Application::Run(HINSTANCE hInstance, int nCmdShow)
{
    if (!m_Window.Create(hInstance, nCmdShow))
        return -1;

    m_Renderer.Initialize(
        m_Window.GetHWND(),
        m_Window.GetWidth(),
        m_Window.GetHeight());

    Time::Init();
    m_Game.Init();

    while (m_IsRunning && m_Window.ProcessMessages())
    {
        Time::Update();

        InputManager::Update();

        m_Game.Update(Time::DeltaTime());

        m_Renderer.BeginFrame();

        m_Game.Render(m_Renderer);

        m_Renderer.EndFrame();
    }

    return 0;
}

