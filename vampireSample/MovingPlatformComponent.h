#pragma once

#include "Component.h"
#include "Vector2.h"
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

private:

    std::vector<Math::Vector2> m_Points;

    int m_CurrentPoint;

    float m_Speed;

    bool m_Loop;
};