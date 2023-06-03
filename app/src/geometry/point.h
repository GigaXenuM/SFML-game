#pragma once

template <typename T> struct Point
{
    Point operator+(const Point &other)
    {
        return { x + other.x, y + other.y };
    }
    Point operator-(const Point &other)
    {
        return { x - other.x, y - other.y };
    }

    T x;
    T y;
};

using PointF = Point<float>;
