#pragma once

#include "Rectangle.h"

struct AnimationFrame
{
    Math::Rectangle SourceRect;

    float Duration = 0.1f;
};