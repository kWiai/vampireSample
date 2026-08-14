#include "src/utilits/Vector2.h"

#include <cmath>
namespace Math
{
    Vector2::Vector2()
    {
        X = 0.0f;
        Y = 0.0f;
    }

    Vector2::Vector2(float x, float y)
    {
        X = x;
        Y = y;
    }

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return Vector2(X + other.X, Y + other.Y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return Vector2(X - other.X, Y - other.Y);
    }

    Vector2 Vector2::operator*(float value) const
    {
        return Vector2(X * value, Y * value);
    }

    Vector2 Vector2::operator/(float value) const
    {
        return Vector2(X / value, Y / value);
    }

    Vector2& Vector2::operator+=(const Vector2& other)
    {
        X += other.X;
        Y += other.Y;

        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& other)
    {
        X -= other.X;
        Y -= other.Y;

        return *this;
    }

    Vector2& Vector2::operator*=(float value)
    {
        X *= value;
        Y *= value;

        return *this;
    }

    Vector2& Vector2::operator/=(float value)
    {
        X /= value;
        Y /= value;

        return *this;
    }

    bool Vector2::operator==(const Vector2& other) const
    {
        return X == other.X && Y == other.Y;
    }

    bool Vector2::operator!=(const Vector2& other) const
    {
        return !(*this == other);
    }

    float Vector2::Length() const
    {
        return std::sqrt(X * X + Y * Y);
    }

    Vector2 Vector2::Normalize() const
    {
        float len = Length();

        if (len == 0.0f)
            return Vector2();

        return Vector2(X / len, Y / len);
    }
}