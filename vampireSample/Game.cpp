#include "Game.h"

#include <gdiplus.h>
#include "ResourceManager.h"
#include "Assets.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "CameraFollowComponent.h"

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

    // Сначала создаем игрока
    auto player = std::make_unique<Player>();
    player->Initialize();

    // Добавляем его в сцену
    m_Scene->AddGameObject(std::move(player));

    // Теперь создаем камеру
    m_Scene->Init();

    m_Scene->GetCamera().SetViewportSize(
        1280.0f,
        720.0f);

    auto camera =
        m_Scene->GetMainCameraObject();

    auto follow =
        camera->AddComponent<CameraFollowComponent>();

    follow->SetTarget(
        m_Scene->FindByName("Player"));
    
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
