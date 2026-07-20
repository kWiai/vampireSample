#pragma once

#include "Render.h"
#include <vector>
#include <memory>
#include "GameObject.h"

class Game
{
public:

    Game();
    ~Game();

    void Init();

    void Update(float deltaTime);

    void Render(Renderer& renderer);

private:

    void UpdateGame(float deltaTime);

    void RenderGame(Renderer& renderer);
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;
};