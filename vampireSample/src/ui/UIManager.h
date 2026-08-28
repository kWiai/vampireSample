#pragma once

#include <memory>
#include <vector>
#include <utility>

#include "UIElement.h"

class Renderer;

class UIManager
{
public:

    UIManager();
    ~UIManager();

    template<typename T, typename... Args>
    T* Create(Args&&... args);

    void Update(float deltaTime);

    void Render(Renderer& renderer);

    void Clear();

private:

    std::vector<
        std::unique_ptr<UIElement>>
        m_Elements;
};

template<typename T, typename... Args>
T* UIManager::Create(
    Args&&... args)
{
    auto element =
        std::make_unique<T>(
            std::forward<Args>(args)...);

    T* pointer =
        element.get();

    m_Elements.push_back(
        std::move(element));

    return pointer;
}