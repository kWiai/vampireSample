#include "src/core/Transform.h"

Transform::Transform()
{
    Position = Math::Vector2(0.0f, 0.0f);

    Size = Math::Vector2(0.0f, 0.0f);

    Scale = Math::Vector2(1.0f, 1.0f);

    Rotation = 0.0f;
}

Transform::~Transform()
{

}