#pragma once

#include "src/components/AnimationClip.h"

class PlayerAnimations
{
public:

    static AnimationClip CreateIdle();

    static AnimationClip CreateWalk();

    // позже
    static AnimationClip CreateRun();
    static AnimationClip CreateAttack();
    static AnimationClip CreateDeath();
};