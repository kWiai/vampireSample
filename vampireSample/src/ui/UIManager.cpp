#include "UIManager.h"

#include "src/rendering/Render.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Update(
    float deltaTime)
{
    for (auto& element : m_Elements)
    {
        if (!element->IsEnabled())
            continue;

        if (!element->IsVisible())
            continue;

        element->Update(
            deltaTime);
    }
}

void UIManager::Render(
    Renderer& renderer)
{
    for (auto& element : m_Elements)
    {
        if (!element->IsVisible())
            continue;

        element->Render(
            renderer);
    }
}

void UIManager::Clear()
{
    m_Elements.clear();
}