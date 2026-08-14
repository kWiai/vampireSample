#include "src/components/AnimationClip.h"

AnimationClip::AnimationClip()
{
    m_Loop = true;
}

AnimationClip::~AnimationClip()
{

}

void AnimationClip::SetName(
    const std::string& name)
{
    m_Name = name;
}

const std::string&
AnimationClip::GetName() const
{
    return m_Name;
}

void AnimationClip::SetLoop(bool loop)
{
    m_Loop = loop;
}

bool AnimationClip::IsLoop() const
{
    return m_Loop;
}

void AnimationClip::SetTexture(
    std::shared_ptr<Texture2D> texture)
{
    m_Texture = texture;
}

std::shared_ptr<Texture2D>
AnimationClip::GetTexture() const
{
    return m_Texture;
}

void AnimationClip::AddFrame(
    const Math::Rectangle& rect,
    float duration)
{
    m_Frames.emplace_back(rect, duration);
}

void AnimationClip::GenerateHorizontal(
    int frameCount,
    int frameWidth,
    int frameHeight,
    float duration)
{
    m_Frames.clear();

    for (int i = 0; i < frameCount; i++)
    {
        AddFrame(
            Math::Rectangle(
                static_cast<float>(i * frameWidth),
                0.0f,
                static_cast<float>(frameWidth),
                static_cast<float>(frameHeight)),
            duration);
    }
}

const AnimationFrame&
AnimationClip::GetFrame(
    int index) const
{
    return m_Frames.at(index);
}

int AnimationClip::GetFrameCount() const
{
    return static_cast<int>(m_Frames.size());
}