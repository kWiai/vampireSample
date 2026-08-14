#include "src/core/Application.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow)
{
    Application app;

    return app.Run(
        hInstance,
        nCmdShow);
}
