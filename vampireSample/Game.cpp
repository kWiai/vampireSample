#include "Game.h"

#include <gdiplus.h>
#include "ResourceManager.h"
#include "Assets.h"
#include "SpriteComponent.h"
using namespace Gdiplus;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
    m_TestObject = std::make_unique<GameObject>();

    // Настраиваем Transform
    m_TestObject->GetTransform().Position = Math::Vector2(300.0f, 200.0f);
    m_TestObject->GetTransform().Size = Math::Vector2(128.0f, 128.0f);

    // Загружаем текстуру
    auto texture =
        ResourceManager::LoadTexture(
            Assets::Textures::PLAYER);

    // Создаем спрайт
    Sprite sprite;

    sprite.SetTexture(texture);

    // Добавляем компонент
    auto spriteComponent =
        m_TestObject->AddComponent<SpriteComponent>();

    // Передаем ему спрайт
    spriteComponent->SetSprite(sprite);
}

void Game::Update(float deltaTime)
{
    if (m_TestObject)
        m_TestObject->Update(deltaTime);
}

void Game::Render(Renderer& renderer)
{
    if (m_TestObject)
        m_TestObject->Render(renderer);
}

