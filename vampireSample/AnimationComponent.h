#pragma once

#include <vector>
#include <string>

#include "Component.h"
#include "Animation.h"

class SpriteComponent;

class AnimationComponent : public Component
{
public:

    AnimationComponent();
    ~AnimationComponent() override;

    void Update(float deltaTime) override;

    void AddAnimation(const Animation& animation);

    bool Play(const std::string& name);

    bool IsPlaying(const std::string& name) const;

    void Stop();

private:

    void ApplyFrame();

private:

    std::vector<Animation> m_Animations;

    Animation* m_CurrentAnimation;

    SpriteComponent* m_Sprite;

    float m_Timer;

    int m_CurrentFrame;

    bool m_Playing;
};