#include "Game.h"

#include <gdiplus.h>
#include "ResourceManager.h"
#include "Assets.h"
#include "Player.h"
#include "SpriteComponent.h"
using namespace Gdiplus;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
    m_Scene = std::make_unique<Scene>();

    auto player = std::make_unique<Player>();

    player->Initialize();

    m_Scene->AddGameObject(std::move(player));
    
}

void Game::Update(float deltaTime)
{
    if (m_Scene)
    {
        m_Scene->Update(deltaTime);
    }
}

void Game::Render(Renderer& renderer)
{
    if (m_Scene)
    {
        m_Scene->Render(renderer);
    }
}
