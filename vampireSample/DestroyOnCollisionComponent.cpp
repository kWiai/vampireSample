#include "DestroyOnCollisionComponent.h"

#include "GameObject.h"

DestroyOnCollisionComponent::DestroyOnCollisionComponent()
{
    m_Delay = 0.0f;
    m_Timer = 0.0f;
    m_Destroying = false;

    m_OnlyPlayer = true;
}

DestroyOnCollisionComponent::~DestroyOnCollisionComponent()
{
}

void DestroyOnCollisionComponent::Update(
    float deltaTime)
{
    if (!m_Destroying)
        return;

    m_Timer -= deltaTime;

    if (m_Timer <= 0.0f)
    {
        if (GetOwner() != nullptr)
        {
            GetOwner()->SetActive(false);
        }

        m_Destroying = false;
    }
}

void DestroyOnCollisionComponent::OnCollisionEnter(
    GameObject* other)
{
    StartDestroyTimer(other);
}

void DestroyOnCollisionComponent::OnTriggerEnter(
    GameObject* other)
{
    StartDestroyTimer(other);
}

void DestroyOnCollisionComponent::StartDestroyTimer(
    GameObject* other)
{
    if (m_Destroying)
        return;

    if (other == nullptr)
        return;

    if (m_OnlyPlayer)
    {
        if (other->GetTag() != "Player")
            return;
    }

    m_Destroying = true;
    m_Timer = m_Delay;
}

void DestroyOnCollisionComponent::SetDelay(
    float delay)
{
    m_Delay = delay;

    if (m_Delay < 0.0f)
        m_Delay = 0.0f;
}

float DestroyOnCollisionComponent::GetDelay() const
{
    return m_Delay;
}

void DestroyOnCollisionComponent::SetOnlyPlayer(
    bool value)
{
    m_OnlyPlayer = value;
}

bool DestroyOnCollisionComponent::GetOnlyPlayer() const
{
    return m_OnlyPlayer;
}