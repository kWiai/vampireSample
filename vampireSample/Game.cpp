#include "Game.h"

#include <gdiplus.h>

using namespace Gdiplus;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
    GameObject* object = new GameObject();

    object->SetName("TestObject");

    object->SetPosition(200, 150);

    object->SetSize(120, 120);

    m_GameObjects.push_back(object);
}

void Game::Update(float deltaTime)
{
    for (GameObject* object : m_GameObjects)
    {
        if (object->IsActive())
        {
            object->Update(deltaTime);
        }
    }
}

void Game::Render(Renderer& renderer)
{
    for (GameObject* object : m_GameObjects)
    {
        if (object->IsActive())
        {
            object->Render(renderer);
        }
    }
}

void Game::UpdateGame(float deltaTime)
{
    // Пока игровой логики нет
}

void Game::RenderGame(Renderer& renderer)
{
    Graphics* graphics = renderer.GetGraphics();

    SolidBrush brush(Color(255, 255, 0, 0));

    graphics->FillRectangle(
        &brush,
        100,
        100,
        150,
        150
    );
}