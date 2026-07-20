#pragma once

namespace Math
{

    class Rectangle
    {
    public:

        Rectangle();

        Rectangle(float x, float y, float width, float height);

    public:

        float x;
        float y;

        float width;
        float height;
    };
}