#pragma once

#include "BaseTypes.h"

namespace G {

    struct Size
    {
        int32 w;
        int32 h;
    };

    struct SizeF
    {
        float w;
        float h;
    };

    struct Pos
    {
        int32 x;
        int32 y;
    };

    struct PosF
    {
        float x;
        float y;
    };

    struct Rect
    {
        int32 l;
        int32 r;
        int32 t;
        int32 b;

        constexpr int32 Width() const { return r - l; }
        constexpr int32 Height() const { return b - t; }
        constexpr bool IsEmpty() const { return  r <= l || b <= t; }
    };

    struct RectF
    {
        float l;
        float r;
        float t;
        float b;

        constexpr float Width() const { return r - l; }
        constexpr float Height() const { return b - t; }
        constexpr bool IsEmpty() const { return  r <= l || b <= t; }
    };
}