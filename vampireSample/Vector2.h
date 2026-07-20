#pragma once

class Vector2
{
public:

    float X;
    float Y;

    Vector2();
    Vector2(float x, float y);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float value) const;
    Vector2 operator/(float value) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float value);
    Vector2& operator/=(float value);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    float Length() const;

    Vector2 Normalize() const;
};