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
    bool Rectangle::Intersects(const Rectangle& other) const
    {
        return
            Left() < other.Right() &&
            Right() > other.Left() &&
            Top() < other.Bottom() &&
            Bottom() > other.Top();
    }

    float Rectangle::Left() const
    {
        return x;
    }

    float Rectangle::Right() const
    {
        return x + width;
    }

    float Rectangle::Top() const
    {
        return y;
    }

    float Rectangle::Bottom() const
    {
        return y + height;
    }

    float Rectangle::CenterX() const
    {
        return x + width * 0.5f;
    }

    float Rectangle::CenterY() const
    {
        return y + height * 0.5f;
    }
}