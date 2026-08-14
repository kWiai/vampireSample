#pragma once

class Time
{
public:
    // Вызывается один раз при запуске приложения
    static void Init();

    // Вызывается каждый кадр
    static void Update();

    // Время между текущим и предыдущим кадром (в секундах)
    static float DeltaTime();

    // Текущий FPS
    static int FPS();

    // Время работы приложения (в секундах)
    static float TotalTime();

private:
    static float m_DeltaTime;
    static float m_TotalTime;

    static int m_FPS;
    static int m_FrameCounter;

    static long long m_LastFrameTime;
    static long long m_LastFPSUpdate;
};