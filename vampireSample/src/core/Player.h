#pragma once

#include "src/core/GameObject.h"
#include "src/components/AnimationComponent.h"

class SpriteComponent;
class PlayerControllerComponent;
class RigidbodyComponent;

class Player : public GameObject
{
public:

    Player();
    virtual ~Player();

    void Initialize();
private:
    SpriteComponent* m_SpriteComponent;

    PlayerControllerComponent* m_PlayerController;

    AnimationComponent* m_Animation;

    RigidbodyComponent* m_Rigidbody;
};
