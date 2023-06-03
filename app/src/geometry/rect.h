#pragma once

#include "point.h"
#include "size.h"

template <typename T> struct Rect
{
    explicit Rect(Point<T> pos, Size<T> size) : pos{ pos }, size{ size }
    {
    }
    explicit Rect(T x, T y, T width, T height) : pos{ x, y }, size{ width, height }
    {
    }

    T width()
    {
        return size.width;
    }
    T height()
    {
        return size.height;
    }

    Point<T> pos;
    Size<T> size;
};

using RectF = Rect<float>;
