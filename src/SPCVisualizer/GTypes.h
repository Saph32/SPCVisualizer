#pragma once

#include "BaseTypes.h"

namespace G {

template <typename T>
struct SizeT {
    T w;
    T h;
};

typedef SizeT<int32> Size;
typedef SizeT<float> SizeF;

template <typename T>
struct PosT {
    T x;
    T y;
};

typedef PosT<int32> Pos;
typedef PosT<float> PosF;

template <typename T>
struct RectT {
    T l;
    T t;
    T r;
    T b;

    constexpr T Width() const { return r - l; }
    constexpr T Height() const { return b - t; }
    constexpr bool  IsEmpty() const { return r <= l || b <= t; }
};

typedef struct RectT<int32> Rect;
typedef struct RectT<float> RectF;

struct Color {
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
};

}  // namespace G