// Game.cpp
#include "Game.h"

#include <gdiplus.h>
#include "ResourceManager.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "AnimationClip.h"
#include "CameraFollowComponent.h"
#include "TileMapComponent.h"
#include "MapLoader.h"
#include "CollisionMatrix.h"
#include "HealthComponent.h"
#include "EnemyControllerComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "MovingPlatformComponent.h"
#include "PlayerControllerComponent.h"
#include "DamageComponent.h"
#include "DestroyOnCollisionComponent.h"
#include "DamageOnCollisionComponent.h" 

using namespace Gdiplus;

static Math::Vector2 V2(float x, float y) { return Math::Vector2(x, y); }

// Вспомогательная функция для создания AnimationClip
static AnimationClip MakeClip(const std::string& name,
    const std::wstring& texturePath,
    int frameCount, int frameWidth, int frameHeight,
    float frameDuration, bool loop)
{
    AnimationClip clip;
    clip.SetName(name);
    clip.SetTexture(ResourceManager::LoadTexture(texturePath));
    clip.GenerateHorizontal(frameCount, frameWidth, frameHeight, frameDuration);
    clip.SetLoop(loop);
    return clip;
}

// ---------- Игрок (player.json) ----------
static void Player(Scene* scene, float x, float y)
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("Player");
    obj->SetTag("Player");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(160.0f, 160.0f);

    auto sprite = obj->AddComponent<SpriteComponent>(); // будет управляться анимацией

    auto anim = obj->AddComponent<AnimationComponent>();
    anim->AddAnimation(MakeClip("Idle", L"Idle-Sheet.png", 8, 64, 64, 0.12f, true));
    anim->AddAnimation(MakeClip("Walk", L"Walk-Sheet.png", 8, 64, 64, 0.08f, true));
    anim->Play("Idle");

    auto rb = obj->AddComponent<RigidbodyComponent>();
    rb->SetUseGravity(false);
    rb->SetGravityScale(1.0f);
    rb->SetMass(1.0f);
    rb->SetKinematic(false);

    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(160.0f, 160.0f);
    col->SetOffset(V2(0.0f, 0.0f));
    col->SetLayer(CollisionLayer::Player);

    auto ctrl = obj->AddComponent<PlayerControllerComponent>();
    ctrl->SetMoveSpeed(300.0f);

    auto health = obj->AddComponent<HealthComponent>();
    health->SetMaxHealth(100.0f);
    health->SetHealth(100.0f);

    scene->AddGameObject(std::move(obj));
}

// ---------- Враг (enemy.json) ----------
static void Enemy(Scene* scene, float x, float y,
    float speed, float viewRadius,
    const std::vector<Math::Vector2>& patrolPoints,
    GameObject* target = nullptr)
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("Enemy");
    obj->SetTag("Enemy");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(160.0f, 160.0f);

    auto sprite = obj->AddComponent<SpriteComponent>();

    auto anim = obj->AddComponent<AnimationComponent>();
    anim->AddAnimation(MakeClip("Idle", L"Idle-Sheet.png", 8, 64, 64, 0.12f, true));
    anim->Play("Idle");

    auto rb = obj->AddComponent<RigidbodyComponent>();
    rb->SetUseGravity(false);
    rb->SetMass(1.0f);
    rb->SetKinematic(false);

    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(140.0f, 140.0f);
    col->SetOffset(V2(10.0f, 10.0f));
    col->SetLayer(CollisionLayer::Default);

    auto ctrl = obj->AddComponent<EnemyControllerComponent>();
    ctrl->SetSpeed(speed);
    ctrl->SetViewRadius(viewRadius);
    for (const auto& pt : patrolPoints)
        ctrl->AddPoint(pt);
    if (target)
        ctrl->SetTarget(target);

    auto health = obj->AddComponent<HealthComponent>();
    health->SetMaxHealth(100.0f);
    health->SetHealth(100.0f);

    auto dmg = obj->AddComponent<DamageComponent>();
    dmg->SetDamage(25.0f);

    scene->AddGameObject(std::move(obj));
}

// ---------- Стена (wall.json) ----------
static void Wall(Scene* scene, float x, float y, float w, float h,
    const std::wstring& texture = L"dirt.png")
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("Wall");
    obj->SetTag("Wall");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(w, h);

    obj->AddComponent<SpriteComponent>()->LoadTexture(texture);

    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(w, h);
    col->SetOffset(V2(0.0f, 0.0f));
    col->SetLayer(CollisionLayer::Wall);
    col->SetTrigger(true);          // обновлено: теперь триггер

    auto dmg = obj->AddComponent<DamageOnCollisionComponent>();
    dmg->SetDamage(25.0f);

    scene->AddGameObject(std::move(obj));
}
// ---------- Движущаяся платформа (MovingPlatform.json) ----------
static void MovingPlatform(Scene* scene, float x, float y, float w, float h,
    float speed, bool loop,
    const std::vector<Math::Vector2>& waypoints,
    const std::wstring& texture = L"stone.png")
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("MovingPlatform");
    obj->SetTag("MovingPlatform");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(w, h);

    obj->AddComponent<SpriteComponent>()->LoadTexture(texture);

    // Коллизия – статическая, как в JSON (без Rigidbody)
    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(w, h);
    col->SetOffset(V2(0.0f, 0.0f));
    col->SetLayer(CollisionLayer::Wall);
    // Trigger = false по умолчанию

    // Движение через компонент
    auto moveComp = obj->AddComponent<MovingPlatformComponent>();
    moveComp->SetSpeed(speed);
    moveComp->SetLoop(loop);
    for (const auto& pt : waypoints)
        moveComp->AddPoint(pt);

    // Здоровье и урон (как в JSON)
    auto health = obj->AddComponent<HealthComponent>();
    health->SetMaxHealth(100.0f);
    health->SetHealth(100.0f);

    auto dmg = obj->AddComponent<DamageComponent>();
    dmg->SetDamage(25.0f);

    scene->AddGameObject(std::move(obj));
}

// ---------- Динамический ящик (DynamicBox.json) ----------
static void DynamicBox(Scene* scene, float x, float y, float w, float h,
    const std::wstring& texture = L"grass.png")
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("DynamicBox");
    obj->SetTag("DynamicBox");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(w, h);

    obj->AddComponent<SpriteComponent>()->LoadTexture(texture);

    auto rb = obj->AddComponent<RigidbodyComponent>();
    rb->SetUseGravity(true);
    rb->SetGravityScale(1.0f);
    rb->SetMass(5.0f);
    rb->SetVelocity(V2(0.0f, 0.0f));   // обновлено: начальная скорость 0
    rb->SetKinematic(false);

    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetTrigger(false);
    col->SetSize(w, h);
    col->SetLayer(CollisionLayer::Wall); // обновлено: слой Wall

    scene->AddGameObject(std::move(obj));
}

// ---------- Карта ----------
static void LoadMap(Scene* scene, const std::string& mapFile)
{
    auto mapObject = std::make_unique<GameObject>();
    auto tileMap = mapObject->AddComponent<TileMapComponent>();
    static TileSet tileSet;
    tileSet.Load(Assets::Textures::TILES, 32, 32);
    tileMap->SetTileSet(&tileSet);
    tileSet.GetTile(1).Solid = true;
    MapLoader::Load(mapFile, tileMap->GetTileMap());

    tileMap->CacheMap();   // ? обязательно!

    scene->AddGameObject(std::move(mapObject));
}
// ---------- Падающая платформа (FallingPlatform.json) ----------
static void FallingPlatform(Scene* scene, float x, float y, float w, float h,
    const std::wstring& texture = L"player.png")
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("FallingPlatform");
    obj->SetTag("FallingPlatform");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(w, h);

    obj->AddComponent<SpriteComponent>()->LoadTexture(texture);

    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(w, h);
    col->SetOffset(V2(0.0f, 0.0f));
    col->SetLayer(CollisionLayer::Wall);
    col->SetTrigger(false);

    // DestroyOnCollisionComponent (добавлен другом)
    auto destroy = obj->AddComponent<DestroyOnCollisionComponent>();
    destroy->SetDelay(2.0f);
    destroy->SetOnlyPlayer(true);

    scene->AddGameObject(std::move(obj));
}
// ---------- Камера ----------
static void SetupCamera(Scene* scene, float viewWidth, float viewHeight, const std::string& followTarget)
{
    scene->Init();
    scene->GetCamera().SetViewportSize(viewWidth, viewHeight);
    auto camObj = scene->GetMainCameraObject();
    auto follow = camObj->AddComponent<CameraFollowComponent>();
    follow->SetTarget(scene->FindByName(followTarget));
}

// ==================== Game ====================

Game::Game() {}
Game::~Game() {}

void Game::Init()
{
    CollisionMatrix::Initialize();
    m_Scene = std::make_unique<Scene>();

    // 1. Карта
    LoadMap(m_Scene.get(), "test.map");

    // 2. Игрок
    Player(m_Scene.get(), 0.0f, 0.0f);

    // 3. Враги 
    GameObject* playerPtr = m_Scene->FindByName("Player");

    // Враг с точным патрулём из enemy.json
    Enemy(m_Scene.get(), 400.0f, 200.0f, 120.0f, 300.0f,
        { V2(800,300), V2(1000,300), V2(1000,500), V2(800,500) },
        playerPtr);

    // Остальные 9 врагов
    for (int i = 0; i < 20; ++i)
    {
        float sx = 400.0f + i * 150.0f;
        float sy = 500.0f - (i % 3) * 50.0f;
        Enemy(m_Scene.get(), sx, sy, 100.0f, 250.0f,
            { V2(sx, sy), V2(sx + 100, sy), V2(sx + 50, sy - 80) },
            playerPtr);
    }

    // 4. Стена (wall.json)
    Wall(m_Scene.get(), 400.0f, 200.0f, 128.0f, 128.0f, L"dirt.png");
    for (int i = 0; i < 20; ++i)
    {
        float sx = 100.0f + i * 150.0f;
        float sy = 1200.0f - (i % 3) * 50.0f;
        Wall(m_Scene.get(), sx, sy, 250, 100,
            L"dirt.png");
    }
    // 5. Движущаяся платформа (MovingPlatform.json)
    MovingPlatform(m_Scene.get(), 300.0f, 300.0f, 160.0f, 32.0f, 100.0f, true,
        { V2(300,300), V2(600,300), V2(600,500), V2(300,500) },
        L"stone.png");

    // 6. Динамический ящик (DynamicBox.json)
    DynamicBox(m_Scene.get(), 500.0f, 100.0f, 64.0f, 64.0f, L"grass.png");
    FallingPlatform(m_Scene.get(), 300.0f, 400.0f, 128.0f, 32.0f, L"player.png");
    // 7. Камера
    SetupCamera(m_Scene.get(), 1280.0f, 720.0f, "Player");
}

void Game::Update(float deltaTime) { if (m_Scene) m_Scene->Update(deltaTime); }
void Game::Render(Renderer& renderer) { if (m_Scene) m_Scene->Render(renderer); }