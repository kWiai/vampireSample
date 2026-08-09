#include "Component.h"

#include "GameObject.h"
#include "Transform.h"

Component::Component()
{
    m_Owner = nullptr;
    m_Enabled = true;
}

Component::~Component()
{
}


// -------------------------
// Lifecycle
// -------------------------

void Component::Start()
{
}

void Component::Update(
    float deltaTime)
{
}

void Component::PhysicsUpdate(
    float deltaTime)
{
}

void Component::LateUpdate(
    float deltaTime)
{
}

void Component::Render(
    Renderer& renderer,
    const Camera& camera)
{
}


// -------------------------
// Collision
// -------------------------

void Component::OnCollisionEnter(
    GameObject* other)
{
}

void Component::OnCollisionStay(
    GameObject* other)
{
}

void Component::OnCollisionExit(
    GameObject* other)
{
}


// -------------------------
// Trigger
// -------------------------

void Component::OnTriggerEnter(
    GameObject* other)
{
}

void Component::OnTriggerStay(
    GameObject* other)
{
}

void Component::OnTriggerExit(
    GameObject* other)
{
}


// -------------------------
// Gameplay Events
// -------------------------

void Component::OnDamage(
    GameObject* attacker,
    float damage)
{
}

void Component::OnDeath()
{
}

void Component::OnAttack(
    GameObject* target)
{
}

void Component::OnInteract(
    GameObject* interactor)
{
}

void Component::OnButtonPressed()
{
}


// -------------------------
// Owner
// -------------------------

void Component::SetOwner(
    GameObject* owner)
{
    m_Owner = owner;
}

GameObject* Component::GetOwner() const
{
    return m_Owner;
}


// -------------------------
// Transform
// -------------------------

Transform& Component::GetTransform()
{
    return m_Owner->GetTransform();
}

const Transform& Component::GetTransform() const
{
    return m_Owner->GetTransform();
}


// -------------------------
// Enabled
// -------------------------

void Component::SetEnabled(
    bool enabled)
{
    m_Enabled = enabled;
}

bool Component::IsEnabled() const
{
    return m_Enabled;
}