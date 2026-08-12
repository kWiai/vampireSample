#pragma once

#include "Component.h"

class GameObject;

class DestroyOnCollisionComponent : public Component
{
public:

    DestroyOnCollisionComponent();
    ~DestroyOnCollisionComponent() override;

    void Update(float deltaTime) override;

    void OnCollisionEnter(
        GameObject* other) override;

    void OnTriggerEnter(
        GameObject* other) override;

    void SetDelay(float delay);
    float GetDelay() const;

    void SetOnlyPlayer(bool value);
    bool GetOnlyPlayer() const;

private:

    void StartDestroyTimer(
        GameObject* other);

private:

    float m_Delay;

    float m_Timer;

    bool m_Destroying;

    bool m_OnlyPlayer;
};