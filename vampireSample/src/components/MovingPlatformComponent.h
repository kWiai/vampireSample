#pragma once

#include "src/core/Component.h"
#include "src/utilits/Vector2.h"
#include <vector>

class MovingPlatformComponent : public Component
{
public:

    MovingPlatformComponent();
    ~MovingPlatformComponent() override;

    void Update(float deltaTime) override;

    void AddPoint(const Math::Vector2& point);

    void SetSpeed(float speed);
    float GetSpeed() const;

    void SetLoop(bool loop);
    bool GetLoop() const;

    const Math::Vector2& GetPreviousPosition() const;
    const Math::Vector2& GetDelta() const;

private:

    int m_CurrentPoint;
    float m_Speed;
    bool m_Loop;

    std::vector<Math::Vector2> m_Points;

    Math::Vector2 m_PreviousPosition;
    Math::Vector2 m_Delta;
};