// Game.cpp
#include "Game.h"

#include <gdiplus.h>
#include "src/utilits/ResourceManager.h"
#include "src/components/Assets.h"
#include "src/components/SpriteComponent.h"
#include "src/components/AnimationComponent.h"
#include "src/components/AnimationClip.h"
#include "src/components/CameraFollowComponent.h"
#include "src/rendering/TileMapComponent.h"
#include "src/rendering/MapLoader.h"
#include "src/physics/CollisionMatrix.h"
#include "src/components/HealthComponent.h"
#include "src/components/EnemyControllerComponent.h"
#include "src/components/RigidbodyComponent.h"
#include "src/components/BoxColliderComponent.h"
#include "src/components/MovingPlatformComponent.h"
#include "src/components/PlayerControllerComponent.h"
#include "src/components/DamageOnCollisionComponent.h"   // компонент урона при столкновении/триггере
#include "src/components/DestroyOnCollisionComponent.h" // компонент самоуничтожения при касании
#include <filesystem>
#include <iostream>
#include <string>
using namespace Gdiplus;

// =================== ГЛОБАЛЬНЫЙ РЕЖИМ ИГРЫ ===================
// true  = боковой вид (платформер) – гравитация работает, W – прыжок
// false = вид сверху (top?down) – гравитация отключена, WASD – свободное перемещение
bool g_IsSideView;

// Вспомогательная функция для создания вектора (x, y) одной строкой
static Math::Vector2 V2(float x, float y) { return Math::Vector2(x, y); }

// Вспомогательная функция для создания анимационного клипа
// Параметры:
//   name          - имя анимации (например, "Idle", "Walk")
//   texturePath   - путь к файлу со спрайт-листом
//   frameCount    - количество кадров
//   frameWidth    - ширина одного кадра в пикселях
//   frameHeight   - высота одного кадра
//   frameDuration - длительность одного кадра в секундах
//   loop          - зациклена ли анимация
static AnimationClip MakeClip(const std::string& name,
    const std::wstring& texturePath,
    int frameCount, int frameWidth, int frameHeight,
    float frameDuration, bool loop)
{
    AnimationClip clip;
    clip.SetName(name);                                                    // задаём имя
    clip.SetTexture(ResourceManager::LoadTexture(texturePath));            // загружаем текстуру
    clip.GenerateHorizontal(frameCount, frameWidth, frameHeight, frameDuration); // нарезаем кадры по горизонтали
    clip.SetLoop(loop);                                                    // зацикливание
    return clip;
}

// =================== ФУНКЦИИ СОЗДАНИЯ ИГРОВЫХ ОБЪЕКТОВ ===================

// ---------- Игрок ----------
static void Player(Scene* scene, float x, float y)
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("Player");                               // Имя (по нему ищем через FindByName)
    obj->SetTag("Player");                                // Тег (группировка, быстрый поиск)
    obj->GetTransform().Position = V2(x, y);              // Стартовая позиция в мире
    obj->GetTransform().Size = V2(160.0f, 160.0f);     // Размер спрайта (и коллайдера)

    // Спрайт – будет заменяться анимацией, но нужен как базовый компонент
    obj->AddComponent<SpriteComponent>();

    // Анимации Idle и Walk
    auto anim = obj->AddComponent<AnimationComponent>();
    anim->AddAnimation(MakeClip("Idle", L"assets/textures/Idle-Sheet.png", 8, 64, 64, 0.12f, true));
    anim->AddAnimation(MakeClip("Walk", L"assets/textures/Walk-Sheet.png", 8, 64, 64, 0.08f, true));
    anim->Play("Idle");                                   // Запускаем Idle

    // Коллайдер (прямоугольный)
    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(160.0f, 160.0f);                         // Размер коллайдера совпадает со спрайтом
    col->SetOffset(V2(0.0f, 0.0f));                       // Без смещения
    col->SetLayer(CollisionLayer::Player);                // Слой игрока (столкновения с Wall, Enemy и т.д.)

    // Контроллер ввода (WASD, прыжок, анимации)
    auto ctrl = obj->AddComponent<PlayerControllerComponent>();
    ctrl->SetMoveSpeed(300.0f);                           // Максимальная скорость движения
    ctrl->SetSideView(g_IsSideView);                      // Передаём текущий режим игры

    // Физическое тело (Rigidbody)
    auto rb = obj->AddComponent<RigidbodyComponent>();
    rb->SetUseGravity(true);                              // Тело хочет гравитации (реально применится, если глобальный флаг разрешает)
    rb->SetGravityScale(1.0f);                            // Обычная сила гравитации
    rb->SetMass(1.0f);                                    // Масса (влияет на выталкивание других тел)
    rb->SetKinematic(false);                              // Не кинематическое (двигаем скоростью)

    // Здоровье
    auto health = obj->AddComponent<HealthComponent>();
    health->SetMaxHealth(100.0f);
    health->SetHealth(100.0f);

    scene->AddGameObject(std::move(obj));                 // Добавляем объект в сцену
}

// ---------- Враг ----------
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

    // Спрайт и анимация Idle
    obj->AddComponent<SpriteComponent>();
    auto anim = obj->AddComponent<AnimationComponent>();
    anim->AddAnimation(MakeClip("Idle", L"assets/textures/Idle-Sheet.png", 8, 64, 64, 0.12f, true));
    anim->Play("Idle");

    // Физическое тело с гравитацией (как и игрок, подчиняется глобальному флагу)
    auto rb = obj->AddComponent<RigidbodyComponent>();
    rb->SetUseGravity(true);
    rb->SetMass(1.0f);
    rb->SetKinematic(false);

    // Коллайдер чуть меньше спрайта и со смещением для более комфортных столкновений
    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(110.0f, 110.0f);                     // высота коллайдера = 60 пикселей
    col->SetOffset(V2(25.0f, 50.0f));
    col->SetLayer(CollisionLayer::Enemy);                 // Слой врага
    col->SetTrigger(false);
    // Контроллер патруля и преследования
    auto ctrl = obj->AddComponent<EnemyControllerComponent>();
    ctrl->SetSpeed(speed);
    ctrl->SetViewRadius(viewRadius);
    for (const auto& pt : patrolPoints) ctrl->AddPoint(pt);
    if (target) ctrl->SetTarget(target);
    ctrl->SetJumpForce(400.0f);   // подберите значение под вашу физику

    // Здоровье
    auto health = obj->AddComponent<HealthComponent>();
    health->SetMaxHealth(100.0f);
    health->SetHealth(100.0f);

    // Урон при столкновении
    auto dmg = obj->AddComponent<DamageOnCollisionComponent>();
    dmg->SetDamage(25.0f);

    scene->AddGameObject(std::move(obj));
}

// ---------- Стена ----------
static void Wall(Scene* scene, float x, float y, float w, float h,
    const std::wstring& texture = L"assets/textures/dirt.png")
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("Wall");
    obj->SetTag("Wall");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(w, h);

    obj->AddComponent<SpriteComponent>()->LoadTexture(texture);  // Текстура стены

    // Твёрдый коллайдер (не триггер)
    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(w, h);
    col->SetOffset(V2(0.0f, 0.0f));
    col->SetLayer(CollisionLayer::Wall);
    col->SetTrigger(false);               // Твёрдое препятствие

    // Урон при касании (если игрок всё же коснётся)
  //  auto dmg = obj->AddComponent<DamageOnCollisionComponent>();
   // dmg->SetDamage(25.0f);

    scene->AddGameObject(std::move(obj));
}

// ---------- Движущаяся платформа ----------
static void MovingPlatform(Scene* scene, float x, float y, float w, float h,
    float speed, bool loop,
    const std::vector<Math::Vector2>& waypoints,
    const std::wstring& texture = L"assets/textures/stone.png")
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("MovingPlatform");
    obj->SetTag("MovingPlatform");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(w, h);

    obj->AddComponent<SpriteComponent>()->LoadTexture(texture);

    // Статический коллайдер (без Rigidbody) – может выталкивать динамические тела
    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(w, h);
    col->SetOffset(V2(0.0f, 0.0f));
    col->SetLayer(CollisionLayer::Wall);                  // Чтобы игрок мог стоять сверху

    // Компонент движения по точкам (кинематическое перемещение)
    auto moveComp = obj->AddComponent<MovingPlatformComponent>();
    moveComp->SetSpeed(speed);
    moveComp->SetLoop(loop);
    for (const auto& pt : waypoints)
        moveComp->AddPoint(pt);

    // Здоровье и урон (опционально, можно убрать)
    auto health = obj->AddComponent<HealthComponent>();
    health->SetMaxHealth(100.0f);
    health->SetHealth(100.0f);

    auto dmg = obj->AddComponent<DamageOnCollisionComponent>();
    dmg->SetDamage(25.0f);

    scene->AddGameObject(std::move(obj));
}

// ---------- Динамический ящик ----------
static void DynamicBox(Scene* scene, float x, float y, float w, float h,
    const std::wstring& texture = L"assets/textures/grass.png")
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("DynamicBox");
    obj->SetTag("DynamicBox");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(w, h);

    obj->AddComponent<SpriteComponent>()->LoadTexture(texture);

    // Физическое тело с гравитацией (падает, можно толкать)
    auto rb = obj->AddComponent<RigidbodyComponent>();
    rb->SetUseGravity(true);
    rb->SetGravityScale(1.0f);
    rb->SetMass(3.0f);                                    // Тяжелее игрока – медленнее толкается
    rb->SetVelocity(V2(0.0f, 0.0f));                      // Начальная скорость нулевая
    rb->SetKinematic(false);

    // Твёрдый коллайдер
    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetTrigger(false);
    col->SetSize(w, h);
    col->SetLayer(CollisionLayer::Wall);                  // Слой Wall, чтобы сталкивался с Player и Enemy

    scene->AddGameObject(std::move(obj));
}

// ---------- Падающая платформа ----------
static void FallingPlatform(Scene* scene, float x, float y, float w, float h,
    const std::wstring& texture = L"assets/textures/player.png")
{
    auto obj = std::make_unique<GameObject>();
    obj->SetName("FallingPlatform");
    obj->SetTag("FallingPlatform");
    obj->GetTransform().Position = V2(x, y);
    obj->GetTransform().Size = V2(w, h);

    obj->AddComponent<SpriteComponent>()->LoadTexture(texture);

    // Твёрдый коллайдер
    auto col = obj->AddComponent<BoxColliderComponent>();
    col->SetSize(w, h);
    col->SetOffset(V2(0.0f, 0.0f));
    col->SetLayer(CollisionLayer::Wall);
    col->SetTrigger(false);

    // Компонент самоуничтожения при касании игрока
    auto destroy = obj->AddComponent<DestroyOnCollisionComponent>();
    destroy->SetDelay(2.0f);                              // Задержка 2 секунды перед исчезновением
    destroy->SetOnlyPlayer(true);                         // Только игрок активирует уничтожение

    scene->AddGameObject(std::move(obj));
}

// ---------- Карта (тайловая) ----------
static void LoadMap(Scene* scene, const std::string& mapFile)
{
    auto mapObject = std::make_unique<GameObject>();
    auto tileMap = mapObject->AddComponent<TileMapComponent>();   // Компонент тайловой карты
    static TileSet tileSet;
    tileSet.Load(Assets::Textures::TILES, 32, 32);                // Загружаем атлас тайлов
    tileMap->SetTileSet(&tileSet);                                // Передаём тайлсет в карту
    tileSet.GetTile(1).Solid = true;                              // Тайл с ID=1 твёрдый
    MapLoader::Load(mapFile, tileMap->GetTileMap());              // Загружаем карту из файла

    tileMap->CacheMap();   // Кэшируем все тайлы в один битмап для быстрой отрисовки

    scene->AddGameObject(std::move(mapObject));
}

// ---------- Камера (настройка) ----------
static void SetupCamera(Scene* scene, float viewWidth, float viewHeight, const std::string& followTarget)
{
    scene->Init();                                                       // Создаём главную камеру внутри сцены
    scene->GetCamera().SetViewportSize(viewWidth, viewHeight);           // Размер игрового экрана (обычно 1280x720)
    auto camObj = scene->GetMainCameraObject();                         // Получаем объект камеры
    auto follow = camObj->AddComponent<CameraFollowComponent>();        // Компонент слежения за целью
    follow->SetTarget(scene->FindByName(followTarget));                 // Указываем цель (игрок)
}

// ==================== ИНИЦИАЛИЗАЦИЯ ИГРЫ ====================
Game::Game() {}
Game::~Game() {}

void Game::Init()
{
    CollisionMatrix::Initialize();                        // Настраиваем слои столкновений
    
    m_Scene = std::make_unique<Scene>();
    // Задаём глобальный режим игры (true – платформер, false – top?down)
    g_IsSideView = true;                                 // пример для top?down, поменяйте на true для бокового вида

    // Синхронизируем гравитацию с глобальным режимом
    PhysicsWorld& physics = m_Scene->GetPhysics();
    physics.SetGlobalGravity(g_IsSideView);



    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string pathStr = "Current working directory: " + currentPath.string() + "\n";
    OutputDebugStringA(pathStr.c_str());
    // 1. Загружаем тайловую карту
    LoadMap(m_Scene.get(), "assets/test.map");

    // 2. Создаём игрока
    Player(m_Scene.get(), 0.0f, 0.0f);

    // 3. Создаём врагов
    GameObject* playerPtr = m_Scene->FindByName("Player");

    // Один враг с конкретным маршрутом 
    Enemy(m_Scene.get(), 400.0f, 200.0f, 120.0f, 300.0f,
        { V2(800,300), V2(1000,300), V2(1000,500), V2(800,500) },
        playerPtr);

    // Ещё 20 врагов, разбросанных по карте
    for (int i = 0; i < 20; ++i)
    {
        float sx = 400.0f + i * 150.0f;
        float sy = 500.0f - (i % 3) * 50.0f;
        Enemy(m_Scene.get(), sx, sy, 100.0f, 250.0f,
            { V2(sx, sy), V2(sx + 100, sy), V2(sx + 50, sy - 80) },
            playerPtr);
    }

    // 4. Стены (одна конкретная + 20 дополнительных)
    Wall(m_Scene.get(), 400.0f, 200.0f, 128.0f, 128.0f, L"assets/textures/dirt.png");
    for (int i = 0; i < 20; ++i)
    {
        float sx = 100.0f + i * 150.0f;
        float sy = 1200.0f - (i % 3) * 50.0f;
        Wall(m_Scene.get(), sx, sy, 250, 100, L"assets/textures/dirt.png");
    }

    // 5. Движущаяся платформа
    MovingPlatform(m_Scene.get(), 300.0f, 300.0f, 160.0f, 32.0f, 100.0f, true,
        { V2(300,300), V2(600,300), V2(600,500), V2(300,500) },
        L"assets/textures/stone.png");

    // 6. Динамический ящик и падающая платформа
    DynamicBox(m_Scene.get(), 500.0f, 100.0f, 64.0f, 64.0f, L"assets/textures/grass.png");
    FallingPlatform(m_Scene.get(), 300.0f, 400.0f, 128.0f, 32.0f, L"assets/textures/player.png");

    // 7. Настройка камеры (должна быть после всех объектов, чтобы FindByName нашёл Player)
    SetupCamera(m_Scene.get(), 1280.0f, 720.0f, "Player");
}

void Game::Update(float deltaTime)
{
    if (m_Scene) m_Scene->Update(deltaTime);
}

void Game::Render(Renderer& renderer)
{
    if (m_Scene) m_Scene->Render(renderer);
}