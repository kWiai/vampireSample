#pragma once

#include "src/core/Component.h"

class GameObject;

class ButtonComponent : public Component
{
public:

    ButtonComponent();
    ~ButtonComponent() override;

    void OnInteract(
        GameObject* interactor) override;

    void SetOnlyPlayer(bool value);
    bool GetOnlyPlayer() const;

    void SetTarget(GameObject* target);
    GameObject* GetTarget() const;

private:

    bool m_OnlyPlayer;

    GameObject* m_Target;
};