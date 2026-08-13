#pragma once

#include "Render.h"
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Scene.h"

class Game
{
public:

    Game();
    ~Game();

    void Init();

    void Update(float deltaTime);

    void Render(Renderer& renderer);

private:

    std::unique_ptr<Scene> m_Scene;
};

