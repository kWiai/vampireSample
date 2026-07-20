#pragma once

#include "Render.h"
#include <vector>

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
    std::vector<GameObject*> m_GameObjects;
};