#pragma once

#include "src/rendering/Rectangle.h"

struct AnimationFrame
{
    Math::Rectangle SourceRect;

    float Duration = 0.1f;
};