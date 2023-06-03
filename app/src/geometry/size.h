#pragma once

template <typename T> struct Size
{
    T width;
    T height;
};

using SizeF = Size<float>;
