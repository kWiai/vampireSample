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

    m_MainCamera = cameraObject.get();

    m_GameObjects.push_back(std::move(cameraObject));
}

void Scene::AddGameObject(std::unique_ptr<GameObject> object)
{
    m_GameObjects.push_back(std::move(object));
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

        if (renderer.IsShowingColliders())
        {
            object->RenderDebug(
                renderer,
                GetCamera());
        }
    }
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

GameObject* Scene::FindByTag(const std::string& tag)
{
    for (auto& object : m_GameObjects)
    {
        if (object->GetTag() == tag)
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
