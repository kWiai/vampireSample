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

    // -------------------------
    // Lifecycle
    // -------------------------

    virtual void Start();

    virtual void Update(
        float deltaTime);

    virtual void PhysicsUpdate(
        float deltaTime);

    virtual void LateUpdate(
        float deltaTime);

    virtual void Render(
        Renderer& renderer,
        const Camera& camera);


    // -------------------------
    // Collision
    // -------------------------

    virtual void OnCollisionEnter(
        GameObject* other);

    virtual void OnCollisionStay(
        GameObject* other);

    virtual void OnCollisionExit(
        GameObject* other);


    // -------------------------
    // Trigger
    // -------------------------

    virtual void OnTriggerEnter(
        GameObject* other);

    virtual void OnTriggerStay(
        GameObject* other);

    virtual void OnTriggerExit(
        GameObject* other);


    // -------------------------
    // Gameplay Events
    // -------------------------

    virtual void OnDamage(
        GameObject* attacker,
        float damage);

    virtual void OnDeath();

    virtual void OnAttack(
        GameObject* target);

    virtual void OnInteract(
        GameObject* interactor);

    virtual void OnButtonPressed();


    // -------------------------
    // Owner
    // -------------------------

    void SetOwner(
        GameObject* owner);

    GameObject* GetOwner() const;


    // -------------------------
    // Transform
    // -------------------------

    Transform& GetTransform();

    const Transform& GetTransform() const;


    // -------------------------
    // Enabled
    // -------------------------

    void SetEnabled(
        bool enabled);

    bool IsEnabled() const;


protected:

    GameObject* m_Owner;

    bool m_Enabled;
};