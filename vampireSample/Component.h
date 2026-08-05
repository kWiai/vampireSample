#pragma once

class GameObject;
class Renderer;
class Transform;
class Camera;

class Component
{
public:

    Component();
    virtual ~Component();

    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Render(
        Renderer& renderer,
        const Camera& camera);
    virtual void OnCollisionEnter(GameObject* other);
    virtual void OnCollisionStay(GameObject* other);
    virtual void OnCollisionExit(GameObject* other);
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