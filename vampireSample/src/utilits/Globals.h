#pragma once

//==================================================
//              Window Settings
//==================================================

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

constexpr wchar_t WINDOW_TITLE[] = L"ENGINE";

//==================================================
//              Engine Settings
//==================================================

constexpr int TARGET_FPS = 60;

constexpr float TARGET_FRAME_TIME = 1.0f / TARGET_FPS;

//==================================================
//              Debug
//==================================================

constexpr bool DEBUG = true;

constexpr bool GRID = true;

//==================================================
//              GAME Settings
//==================================================

constexpr bool GRAVITY = false;

//==================================================
//              Game States
//==================================================

enum class GameState
{
    MainMenu,
    Playing,
    Pause,
    Exit
};