#pragma once

#include <memory>
#include <vector>
#include <string> 

class GameObject;
class Renderer;

class Scene
{
public:

    Scene();
    virtual ~Scene();

    virtual void Init();

    virtual void Update(float deltaTime);

    virtual void Render(Renderer& renderer);

    GameObject* FindByName(const std::string& name);

    GameObject* FindByTag(const std::string& tag);

    std::vector<GameObject*> FindAllByTag(const std::string& tag);

    void AddGameObject(std::unique_ptr<GameObject> object);

private:

    std::vector<std::unique_ptr<GameObject>> m_GameObjects;
};