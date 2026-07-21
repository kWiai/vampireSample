#pragma once

class GameObject;
class Renderer;
class Transform;

class Component
{
public:

    Component();
    virtual ~Component();

    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Render(Renderer& renderer);

    void SetOwner(GameObject* owner);

    GameObject* GetOwner() const;

    Transform& GetTransform();
    const Transform& GetTransform() const;

    void SetEnabled(bool enabled);

    bool IsEnabled() const;

protected:

    GameObject* m_Owner;

    bool m_Enabled;
};