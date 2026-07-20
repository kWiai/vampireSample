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
    auto object = std::make_unique<GameObject>();

    object->SetName("TestObject");

    object->GetTransform().Position = Vector2(200, 150);

    object->GetTransform().Size = Vector2(120, 120);

    m_GameObjects.push_back(std::move(object));
}

void Game::Update(float deltaTime)
{
    for (const auto& object : m_GameObjects)
    {
        if (object->IsActive())
        {
            object->Update(deltaTime);
        }
    }
}

void Game::Render(Renderer& renderer)
{
    for (const auto& object : m_GameObjects)
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