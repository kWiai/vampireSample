#include "Scene.h"

#include "GameObject.h"
#include "Render.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::Init()
{

}

void Scene::AddGameObject(std::unique_ptr<GameObject> object)
{
    m_GameObjects.push_back(std::move(object));
}

void Scene::Update(float deltaTime)
{
    for (auto& object : m_GameObjects)
    {
        if (object->IsActive())
        {
            object->Update(deltaTime);
        }
    }
}

void Scene::Render(Renderer& renderer)
{
    for (auto& object : m_GameObjects)
    {
        if (object->IsActive())
        {
            object->Render(renderer);
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