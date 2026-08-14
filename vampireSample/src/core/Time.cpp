#include "src/core/Time.h"

#include <windows.h>

float Time::m_DeltaTime = 0.0f;
float Time::m_TotalTime = 0.0f;

int Time::m_FPS = 0;
int Time::m_FrameCounter = 0;

long long Time::m_LastFrameTime = 0;
long long Time::m_LastFPSUpdate = 0;

void Time::Init()
{
    m_LastFrameTime = GetTickCount64();
    m_LastFPSUpdate = m_LastFrameTime;

    m_DeltaTime = 0.0f;
    m_TotalTime = 0.0f;

    m_FrameCounter = 0;
    m_FPS = 0;
}

void Time::Update()
{
    long long current = GetTickCount64();

    m_DeltaTime = (current - m_LastFrameTime) / 1000.0f;
    m_LastFrameTime = current;

    m_TotalTime += m_DeltaTime;

    m_FrameCounter++;

    if (current - m_LastFPSUpdate >= 1000)
    {
        m_FPS = m_FrameCounter;

        m_FrameCounter = 0;
        m_LastFPSUpdate = current;
    }
}

float Time::DeltaTime()
{
    return m_DeltaTime;
}

int Time::FPS()
{
    return m_FPS;
}


float Time::TotalTime()
{
    return m_TotalTime;
}