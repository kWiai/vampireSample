#pragma once

#include <vector>
#include <string>

#include "src/core/Component.h"
#include "AnimationClip.h"

class SpriteComponent;

class AnimationComponent : public Component
{
public:

    AnimationComponent();
    ~AnimationComponent() override;

    void Update(float deltaTime) override;

    void AddAnimation(
        const AnimationClip& animation);

    bool Play(const std::string& name);

    bool IsPlaying(const std::string& name) const;

    void Stop();

private:

    void ApplyFrame();

private:

    std::vector<AnimationClip> m_Animations;

    AnimationClip* m_CurrentAnimation;

    SpriteComponent* m_Sprite;

    float m_Timer;

    int m_CurrentFrame;

    bool m_Playing;
};