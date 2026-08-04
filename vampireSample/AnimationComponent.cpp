#include "AnimationComponent.h"

#include "SpriteComponent.h"
#include "GameObject.h"

AnimationComponent::AnimationComponent()
{
    m_CurrentAnimation = nullptr;

    m_Sprite = nullptr;

    m_Timer = 0.0f;

    m_CurrentFrame = 0;

    m_Playing = false;
}

AnimationComponent::~AnimationComponent()
{

}

void AnimationComponent::Update(float deltaTime)
{
    if (!m_Playing)
        return;

    if (m_CurrentAnimation == nullptr)
        return;

    if (m_Sprite == nullptr)
    {
        m_Sprite =
            GetOwner()->GetComponent<SpriteComponent>();

        if (m_Sprite == nullptr)
            return;
    }

    m_Timer += deltaTime;

    const AnimationFrame& frame =
        m_CurrentAnimation->GetFrame(m_CurrentFrame);

    if (m_Timer < frame.Duration)
        return;

    m_Timer = 0.0f;

    m_CurrentFrame++;

    if (m_CurrentFrame >=
        m_CurrentAnimation->GetFrameCount())
    {
        if (m_CurrentAnimation->IsLoop())
        {
            m_CurrentFrame = 0;
        }
        else
        {
            m_CurrentFrame =
                m_CurrentAnimation->GetFrameCount() - 1;

            m_Playing = false;
        }
    }

    ApplyFrame();
}

void AnimationComponent::ApplyFrame()
{
    if (m_CurrentAnimation == nullptr)
        return;

    if (m_Sprite == nullptr)
        return;

    m_Sprite->GetSprite().SetSourceRect(
        m_CurrentAnimation
        ->GetFrame(m_CurrentFrame)
        .SourceRect);
}

void AnimationComponent::AddAnimation(
    const Animation& animation)
{
    m_Animations.push_back(animation);
}

bool AnimationComponent::Play(
    const std::string& name)
{
    if (IsPlaying(name))
        return false;

    if (m_Sprite == nullptr)
    {
        m_Sprite =
            GetOwner()->GetComponent<SpriteComponent>();
    }

    for (auto& animation : m_Animations)
    {
        if (animation.GetName() == name)
        {
            m_CurrentAnimation = &animation;
            m_CurrentFrame = 0;
            m_Timer = 0.0f;
            m_Playing = true;

            ApplyFrame();

            return true;
        }
    }

    return false;
}

bool AnimationComponent::IsPlaying(
    const std::string& name) const
{
    if (!m_Playing)
        return false;

    if (m_CurrentAnimation == nullptr)
        return false;

    return
        m_CurrentAnimation->GetName() == name;
}

void AnimationComponent::Stop()
{
    m_Playing = false;
}