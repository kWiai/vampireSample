#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <map>
#pragma comment(lib, "gdiplus.lib")
#include <vector>
#include <string>
#include <chrono>

using namespace Gdiplus;
using namespace std;
Image* menu_image = nullptr;
Image* map_image = nullptr;
Image* hero_image = nullptr;
POINT p;

struct maps {
    float posX;
    float posY;
    const wchar_t* mapImage;
};
struct walkImages {
    const wchar_t* leftImage;
    const wchar_t* stateImage;
    const wchar_t* rightImage;
};

vector<maps> mm{ { -100.0f, -100.0f, L"mapTest.png" } };

enum class currentDirection_ { left, right, state };

class Hero {
public:
    int currentMapID;
    int step;
    currentDirection_ currentDirection;
    walkImages imageSet{};
    std::chrono::steady_clock::time_point lastUpdate;
    float moveSpeed;

    Hero(int mapID, int s, currentDirection_ dir, walkImages images, float speed = 100.0f)
        : currentMapID(mapID), step(s), currentDirection(dir), imageSet(images),
        moveSpeed(speed), lastUpdate(std::chrono::steady_clock::now()) {
    }

    void move() {
        auto now = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastUpdate).count();
        lastUpdate = now;

        if (deltaTime > 0.1f) deltaTime = 0.1f;

        float moveAmount = moveSpeed * deltaTime;
        bool isMoving = false;

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            mm[currentMapID].posX -= moveAmount;
            currentDirection = currentDirection_::right;
            isMoving = true;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            mm[currentMapID].posX += moveAmount;
            currentDirection = currentDirection_::left;
            isMoving = true;
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            mm[currentMapID].posY += moveAmount;
            isMoving = true;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            mm[currentMapID].posY -= moveAmount;
            isMoving = true;
        }

        if (!isMoving && (currentDirection == currentDirection_::left ||
            currentDirection == currentDirection_::right)) {
            currentDirection = currentDirection_::state;
        }
    }

    void drawHero(Graphics& graphics, int width, int height) {
        const wchar_t* imagePath = L"";

        if (currentDirection == currentDirection_::left) {
            imagePath = imageSet.leftImage;
        }
        else if (currentDirection == currentDirection_::state) {
            imagePath = imageSet.stateImage;
        }
        else if (currentDirection == currentDirection_::right) {
            imagePath = imageSet.rightImage;
        }

        Image heroImage(imagePath);
        if (heroImage.GetLastStatus() == Ok) {
            hero_image = heroImage.GetThumbnailImage(100, 100, nullptr, nullptr);
            if (hero_image) {
                graphics.DrawImage(hero_image, width / 2, height / 2);
            }
        }
    }
};

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