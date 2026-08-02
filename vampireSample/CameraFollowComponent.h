#pragma once

#include "Component.h"

#include "Vector2.h"

class GameObject;

class CameraFollowComponent : public Component
{
public:

    CameraFollowComponent();
    ~CameraFollowComponent() override;

    void Update(float deltaTime) override;

    void SetTarget(GameObject* target);

    GameObject* GetTarget() const;

    void SetOffset(const Math::Vector2& offset);

    const Math::Vector2& GetOffset() const;

    void SetFollowX(bool follow);

    void SetFollowY(bool follow);

private:

    GameObject* m_Target;

    Math::Vector2 m_Offset;

    bool m_FollowX;

    bool m_FollowY;
};