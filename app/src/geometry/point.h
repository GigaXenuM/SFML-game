#pragma once

template <typename T> struct Point
{
    Point operator+(const Point &other) const
    {
        return { x + other.x, y + other.y };
    }
    Point operator-(const Point &other) const
    {
        return { x - other.x, y - other.y };
    }
    Point &operator+=(const Point &other) const
    {
        return *this = *this + other;
    }
    Point &operator-=(const Point &other) const
    {
        return *this = *this - other;
    }
    Point operator/(T value) const
    {
        return { x / value, y / value };
    }
    Point operator*(T value) const
    {
        return { x * value, y * value };
    }
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }

    bool isDefault() const
    {
        return x == T() && y == T();
    }

    T x;
    T y;
};

using PointF = Point<float>;
using PointI = Point<int>;
