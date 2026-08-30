#pragma once

#include "src/rendering/Render.h"
#include <vector>
#include <memory>
#include "src/core/GameObject.h"
#include "Scene.h"
#include "src/ui/UIManager.h"

class Game
{
public:

    Game();
    ~Game();

    void Init();

    void Update(float deltaTime);

    void Render(Renderer& renderer);

    Scene* GetScene();

private:

    std::unique_ptr<Scene> m_Scene;
    UIManager m_UIManager;
};

