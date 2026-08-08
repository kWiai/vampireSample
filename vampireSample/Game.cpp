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

    // Сначала создаем игрока
    //auto player = std::make_unique<Player>();
    //player->Initialize();

    // Добавляем его в сцену
    EntityDefinition definition;

    EntityManager entityManager;

    auto player =
        entityManager.Create("Player");

    
    if (player)
    {
        player->SetName("Player");
        player->SetTag("Player");

        m_Scene->AddGameObject(std::move(player));
    }
    
    auto enemy =
        entityManager.Create("Enemy");

    if (enemy)
    {
        enemy->SetName("Enemy");
        enemy->SetTag("Enemy");

        m_Scene->AddGameObject(std::move(enemy));
    }

    EntityDefinition wallDefinition;

    wallDefinition.Name = "Wall";

    wallDefinition.Position =
        Math::Vector2(400.0f, 400.0f);

    wallDefinition.Size =
        Math::Vector2(160.0f, 160.0f);


    // Sprite
    wallDefinition.HasSprite = true;

    wallDefinition.Texture =
        Assets::Textures::STONE;


    // Animation
    wallDefinition.HasAnimation = false;

    wallDefinition.Idle.HasAnimation = false;
   

    wallDefinition.Walk.HasAnimation = false;
    


    // Rigidbody
    wallDefinition.HasRigidbody = false;
    wallDefinition.UseGravity = false;
    wallDefinition.Kinematic = false;


    // Collider
    wallDefinition.HasCollider = true;
    wallDefinition.ColliderSize =
        Math::Vector2(160.0f, 160.0f);

    wallDefinition.Layer =
        CollisionLayer::Wall;


    // Controller
    wallDefinition.HasPlayerController = false;
    


    Prefab wallPrefab;

    wallPrefab.SetDefinition(
        wallDefinition);

    auto wall =
        wallPrefab.Instantiate();

    wall->SetName("Wall");
    wall->SetTag("Wall");

    m_Scene->AddGameObject(std::move(wall));

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
