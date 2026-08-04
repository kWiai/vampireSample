#pragma once

#include <vector>
#include <string>

#include "AnimationFrame.h"

class Animation
{
public:

    Animation();
    ~Animation();

    void AddFrame(
        const Math::Rectangle& rect,
        float duration);

    const AnimationFrame& GetFrame(int index) const;

    int GetFrameCount() const;

    void SetLoop(bool loop);
    bool IsLoop() const;

    void SetName(const std::string& name);
    const std::string& GetName() const;

private:

    std::string m_Name;

    std::vector<AnimationFrame> m_Frames;

    bool m_Loop;
};