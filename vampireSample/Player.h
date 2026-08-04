#pragma once

#include "GameObject.h"
#include "AnimationComponent.h"

class SpriteComponent;
class PlayerControllerComponent;

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
};
