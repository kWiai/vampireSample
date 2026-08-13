#include "Scene.h"

#include "GameObject.h"
#include "Render.h"


Scene::Scene()
{
    m_MainCamera = nullptr;
}

Scene::~Scene()
{

}

void Scene::Init()
{
    auto cameraObject =
        std::make_unique<GameObject>();

    cameraObject->SetName("MainCamera");

    cameraObject->SetTag("Camera");

    auto cameraComponent =
        cameraObject->AddComponent<CameraComponent>();

    cameraObject->SetScene(this);

    m_MainCamera = cameraObject.get();

    m_GameObjects.push_back(std::move(cameraObject));
}

void Scene::AddGameObject(std::unique_ptr<GameObject> object)
{
    object->SetScene(this);

    m_GameObjects.push_back(std::move(object));
}

void Scene::ProcessDestroyQueue()
{
    auto it = m_GameObjects.begin();
    while (it != m_GameObjects.end())
    {
        if ((*it)->IsPendingDestroy())
            it = m_GameObjects.erase(it);
        else
            ++it;
    }
}

void Scene::RemoveGameObject(GameObject* obj)
{
    auto it = std::find_if(m_GameObjects.begin(), m_GameObjects.end(),
        [obj](const std::unique_ptr<GameObject>& ptr) { return ptr.get() == obj; });
    if (it != m_GameObjects.end())
        m_GameObjects.erase(it);
}

const std::vector<std::unique_ptr<GameObject>>&
Scene::GetGameObjects() const
{
    return m_GameObjects;
}

void Scene::Update(float deltaTime)
{
    // 1. Логика (ввод, AI, анимации и т.д.)
    for (auto& object : m_GameObjects)
    {
        if (!object->IsActive())
            continue;

        if (object->GetParent())
            continue;

        object->Update(deltaTime);
    }

    // 2. Физика компонентов (Rigidbody и т.п.)
    for (auto& object : m_GameObjects)
    {
        if (!object->IsActive())
            continue;

        if (object->GetParent())
            continue;

        object->PhysicsUpdate(deltaTime);
    }

    // 3. Проверка и разрешение столкновений
    m_Physics.Update(*this, deltaTime);
    ProcessDestroyQueue();
    m_Events.Update();
    m_Events.Clear();


    // 4. Позднее обновление (камера, следящие системы)
    for (auto& object : m_GameObjects)
    {
        if (!object->IsActive())
            continue;

        if (object->GetParent())
            continue;

        object->LateUpdate(deltaTime);
    }
}

void Scene::Render(Renderer& renderer)
{
    renderer.DrawGrid(GetCamera());
    for (auto& object : m_GameObjects)
    {
        if (!object->IsActive())
            continue;

        // Рисуем только корневые объекты
        if (object->GetParent() != nullptr)
            continue;

        object->Render(
            renderer,
            GetCamera());

        object->RenderDebug(
            renderer,
            GetCamera());

    }
    m_Physics.RenderDebug(
        renderer,
        GetCamera());
}
GameObject* Scene::FindByName(const std::string& name)
{
    for (auto& object : m_GameObjects)
    {
        if (object->GetName() == name)
        {
            return object.get();
        }
    }

    return nullptr;
}

std::vector<GameObject*> Scene::FindAllByTag(const std::string& tag)
{
    std::vector<GameObject*> result;

    for (auto& object : m_GameObjects)
    {
        if (object->GetTag() == tag)
        {
            result.push_back(object.get());
        }
    }

    return result;
}



Camera& Scene::GetCamera()
{
    return GetMainCamera()->GetCamera();
}

const Camera& Scene::GetCamera() const
{
    return m_MainCamera
        ->GetComponent<CameraComponent>()
        ->GetCamera();
}

PhysicsWorld& Scene::GetPhysics()
{
    return m_Physics;
}

const PhysicsWorld& Scene::GetPhysics() const
{
    return m_Physics;
}

GameObject* Scene::GetMainCameraObject()
{
    return m_MainCamera;
}
CameraComponent* Scene::GetMainCamera()
{
    if (m_MainCamera == nullptr)
    {
        return nullptr;
    }

    return m_MainCamera->GetComponent<CameraComponent>();
}
EventManager& Scene::GetEvents()
{
    return m_Events;
}

const EventManager& Scene::GetEvents() const
{
    return m_Events;
}
