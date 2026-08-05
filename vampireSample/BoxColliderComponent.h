#pragma once

#include "Component.h"
#include "Vector2.h"

class BoxColliderComponent : public Component
{
public:

    BoxColliderComponent();
    ~BoxColliderComponent() override;

    void SetSize(float width, float height);
    Math::Vector2 GetSize() const;

    void SetOffset(const Math::Vector2& offset);
    Math::Vector2 GetOffset() const;

    void SetTrigger(bool trigger);
    bool IsTrigger() const;

    Math::Vector2 GetMin() const;
    Math::Vector2 GetMax() const;

private:

    Math::Vector2 m_Size;
    Math::Vector2 m_Offset;

    bool m_IsTrigger;
};