#pragma once
#include "Camera.h"
#include <memory>
#include <vector>
#include <string> 
#include "CameraComponent.h"
#include "PhysicsWorld.h"

class GameObject;
class Renderer;

class Scene
{
public:

    Scene();
    virtual ~Scene();

    virtual void Init();

    virtual void Update(float deltaTime);

    void Render(Renderer& renderer);

    GameObject* FindByName(const std::string& name);

    GameObject* FindByTag(const std::string& tag);

    Camera& GetCamera();

    const Camera& GetCamera() const;

    GameObject* GetMainCameraObject();

    CameraComponent* GetMainCamera();

    PhysicsWorld& GetPhysics();

    const PhysicsWorld& GetPhysics() const;

    std::vector<GameObject*> FindAllByTag(const std::string& tag);

    void AddGameObject(std::unique_ptr<GameObject> object);

    const std::vector<std::unique_ptr<GameObject>>&
        GetGameObjects() const;

private:
    GameObject* m_MainCamera;
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;
    PhysicsWorld m_Physics;
};