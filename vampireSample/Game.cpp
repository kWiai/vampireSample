#include "Game.h"

#include <gdiplus.h>
#include "ResourceManager.h"
#include "Assets.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "CameraFollowComponent.h"
#include "TileMapComponent.h"
#include "MapLoader.h"
#include "CollisionMatrix.h"
#include "EntityFactory.h"
#include "EntityDefinition.h"
#include "Prefab.h"
#include "EntityLoader.h"
#include "EntityManager.h"
#include "TestDamageComponent.h"
#include "Damage.h"
#include "HealthComponent.h"
#include "EnemyControllerComponent.h"


using namespace Gdiplus;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
    CollisionMatrix::Initialize();

    m_Scene = std::make_unique<Scene>();

    auto mapObject =
        std::make_unique<GameObject>();

    auto tileMap =
        mapObject->AddComponent<TileMapComponent>();

    static TileSet tileSet;

    tileSet.Load(
        Assets::Textures::TILES,
        32,
        32);

    tileMap->SetTileSet(&tileSet);

    tileSet.GetTile(1).Solid = true;

    MapLoader::Load(
        "test.map",
        tileMap->GetTileMap());
    auto& map =
        tileMap->GetTileMap();

    

    m_Scene->AddGameObject(
        std::move(mapObject));

  
    EntityDefinition definition;

    EntityManager entityManager;

    auto player =
        entityManager.Create("Player");

    if (player)
    {
        player->SetName("Player");
        player->SetTag("Player");
        m_Scene->AddGameObject(
            std::move(player));
    }

    auto enemy =
        entityManager.Create("Enemy");

    if (enemy)
    {
        enemy->SetName("Enemy");
        enemy->SetTag("Enemy");

        auto playerObject =
            m_Scene->FindByName("Player");

        auto controller =
            enemy->GetComponent<
            EnemyControllerComponent>();

        if (controller != nullptr)
        {
            controller->SetTarget(
                playerObject);
        }

        m_Scene->AddGameObject(
            std::move(enemy));
    }

    auto wall =
        entityManager.Create("Wall");

    if (wall)
    {
        wall->SetName("Wall");
        wall->SetTag("Wall");

        m_Scene->AddGameObject(std::move(wall));
    }

    auto moving_platform =
        entityManager.Create("Moving_platform");

    if (moving_platform)
    {
        moving_platform->SetName("Moving_platform");
        moving_platform->SetTag("Moving_platform");

        m_Scene->AddGameObject(std::move(moving_platform));
    }


    auto dynamic_box =
        entityManager.Create("DynamicBox");

    if (dynamic_box)
    {
        dynamic_box->SetName("DynamicBox");
        dynamic_box->SetTag("DynamicBox");

        m_Scene->AddGameObject(std::move(dynamic_box));
    }

    
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
