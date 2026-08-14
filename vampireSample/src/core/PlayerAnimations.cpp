#include "PlayerAnimations.h"

#include "src/components/Assets.h"
#include "src/utilits/ResourceManager.h"

AnimationClip PlayerAnimations::CreateIdle()
{
    AnimationClip clip;

    clip.SetName("Idle");

    clip.SetTexture(
        ResourceManager::LoadTexture(
            Assets::Textures::PLAYER_IDLE));

    clip.GenerateHorizontal(
        8,
        640,
        640,
        0.12f);

    clip.SetLoop(true);

    return clip;
}

AnimationClip PlayerAnimations::CreateWalk()
{
    AnimationClip clip;

    clip.SetName("Walk");

    clip.SetTexture(
        ResourceManager::LoadTexture(
            Assets::Textures::PLAYER_WALK));

    clip.GenerateHorizontal(
        8,
        640,
        640,
        0.08f);

    clip.SetLoop(true);

    return clip;
}