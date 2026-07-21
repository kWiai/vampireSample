#pragma once

#include "Component.h"

class PlayerControllerComponent : public Component
{
public:

    PlayerControllerComponent();
    ~PlayerControllerComponent();

    void Update(float deltaTime) override;

    void SetMoveSpeed(float speed);

private:

    float m_MoveSpeed;
};