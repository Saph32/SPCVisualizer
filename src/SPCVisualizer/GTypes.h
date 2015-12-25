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
    T r;
    T t;
    T b;

    constexpr int32 Width() const { return r - l; }
    constexpr int32 Height() const { return b - t; }
    constexpr bool  IsEmpty() const { return r <= l || b <= t; }
};

typedef struct RectT<int32> Rect;
typedef struct RectT<float> RectF;
}