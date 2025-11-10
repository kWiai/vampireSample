#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <map>
#pragma comment(lib, "gdiplus.lib")
#include <vector>


class Hero {

};


using namespace Gdiplus;
using namespace std;
Image* menu_image = nullptr;
POINT p;

enum class gameState_ {
    MainMenu, game, pause
};
const wchar_t* musicPath = nullptr;
gameState_  gameState = gameState_::MainMenu;
int playButtonX1;
int playButtonX2;
int playButtonY1;
int playButtonY2;
bool init = false;