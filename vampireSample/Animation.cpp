#include "Animation.h"

Animation::Animation()
{
    m_Loop = true;
}

Animation::~Animation()
{

}

void Animation::AddFrame(
    const Math::Rectangle& rect,
    float duration)
{
    AnimationFrame frame;

    frame.SourceRect = rect;
    frame.Duration = duration;

    m_Frames.push_back(frame);
}

const AnimationFrame&
Animation::GetFrame(int index) const
{
    return m_Frames.at(index);
}

int Animation::GetFrameCount() const
{
    return static_cast<int>(m_Frames.size());
}

void Animation::SetLoop(bool loop)
{
    m_Loop = loop;
}

bool Animation::IsLoop() const
{
    return m_Loop;
}

void Animation::SetName(const std::string& name)
{
    m_Name = name;
}

const std::string&
Animation::GetName() const
{
    return m_Name;
}