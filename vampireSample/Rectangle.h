#pragma once

namespace Math
{

    class Rectangle
    {
    public:

        Rectangle();

        Rectangle(float x, float y, float width, float height);

        bool Intersects(const Rectangle& other) const;

        float Left() const;
        float Right() const;

        float Top() const;
        float Bottom() const;

        float CenterX() const;
        float CenterY() const;

    public:

        float x;
        float y;

        float width;
        float height;
    };
}