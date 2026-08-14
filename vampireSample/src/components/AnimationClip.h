#pragma once

#include <string>
#include <vector>
#include <memory>

#include "AnimationFrame.h"
#include "src/rendering/Texture2D.h"

class AnimationClip
{
public:

    AnimationClip();
    ~AnimationClip();

    void SetName(const std::string& name);
    const std::string& GetName() const;

    void SetLoop(bool loop);
    bool IsLoop() const;

    void SetTexture(
        std::shared_ptr<Texture2D> texture);

    std::shared_ptr<Texture2D>
        GetTexture() const;

    void AddFrame(
        const Math::Rectangle& rect,
        float duration);

    void GenerateHorizontal(
        int frameCount,
        int frameWidth,
        int frameHeight,
        float duration);

    const AnimationFrame&
        GetFrame(int index) const;

    int GetFrameCount() const;

private:

    std::string m_Name;

    bool m_Loop;

    std::shared_ptr<Texture2D> m_Texture;

    std::vector<AnimationFrame> m_Frames;
};