#pragma once

#include "Component.h"
#include "Vector2.h"
#include "AABB.h"
#include "CollisionLayer.h"
#include "PhysicsMaterial.h"

class BoxColliderComponent : public Component
{
public:

    BoxColliderComponent();
    ~BoxColliderComponent() override;

    void SetSize(float width, float height);
    Math::Vector2 GetSize() const;

    void SetOffset(const Math::Vector2& offset);
    Math::Vector2 GetOffset() const;
    void Render(
        Renderer& renderer,
        const Camera& camera) override;
    void SetTrigger(bool trigger);
    bool IsTrigger() const;
    Physics::AABB GetBounds() const;
    Math::Vector2 GetMin() const;
    Math::Vector2 GetMax() const;
    Math::Vector2 GetCenter() const;
    void SetLayer(CollisionLayer layer);
    CollisionLayer GetLayer() const;
    PhysicsMaterial& GetMaterial();

    const PhysicsMaterial& GetMaterial() const;

private:

    Math::Vector2 m_Size;
    Math::Vector2 m_Offset;

    bool m_IsTrigger;
    CollisionLayer m_Layer;
    PhysicsMaterial m_Material;
};