#include "Rectangle.h"
namespace Math
{
    Rectangle::Rectangle()
    {
        x = 0.0f;
        y = 0.0f;

        width = 0.0f;
        height = 0.0f;
    }

    Rectangle::Rectangle(float x, float y, float width, float height)
    {
        this->x = x;
        this->y = y;

        this->width = width;
        this->height = height;
    }
}