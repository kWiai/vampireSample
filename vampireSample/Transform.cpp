#include "Transform.h"

Transform::Transform()
{
    Position = Vector2(0.0f, 0.0f);

    Size = Vector2(0.0f, 0.0f);

    Scale = Vector2(1.0f, 1.0f);

    Rotation = 0.0f;
}

Transform::~Transform()
{

}