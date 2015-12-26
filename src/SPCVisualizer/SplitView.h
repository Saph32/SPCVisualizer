#pragma once

#include "GTypes.h"

namespace G {
struct SplitView {
    constexpr SplitView() {}
    constexpr SplitView(const SplitView& rOther) = default;
    constexpr SplitView(const RectF& rRect) : rect(rRect) {}
    constexpr SplitView(const RectF& rRect, const Size& rSplit)
        : rect(rRect), split{static_cast<float>(rSplit.w), static_cast<float>(rSplit.h)} {}
    constexpr SplitView(const RectF& rRect, const SizeF& rSplit) : rect(rRect), split(rSplit) {}

    constexpr RectF Cell(int32 x, int32 y) const {
        return Cell(static_cast<float>(x), static_cast<float>(y));
    }

    constexpr RectF Cell(float x, float y) const { return Sub(x, y, x + 1, y + 1); }

    constexpr RectF Sub(float x, float y, float w, float h) const {
        return RectF{rect.l + (rect.Width() / split.w) * x,
                     rect.t + (rect.Height() / split.h) * y,
                     rect.l + (rect.Width() / split.w) * (x + w),
                     rect.t + (rect.Height() / split.h) * (y + h)};
    }

    constexpr operator RectF() const { return rect; }

    const RectF rect  = {0, 0, 1, 1};
    const SizeF split = {1, 1};
};

struct SplitViewH : public SplitView{
    constexpr SplitViewH() : SplitView() {}
    constexpr SplitViewH(const SplitViewH& rOther) = default;
    constexpr SplitViewH(const RectF& rRect, int32 splitParam)
        : SplitView(rRect, Size{splitParam, 1}) {}
    constexpr SplitViewH(const RectF& rRect, float splitParam)
        : SplitView(rRect, SizeF{splitParam, 1 }) {}

    constexpr RectF Cell(int32 x) const { return SplitView::Cell(x, 0); }
    constexpr RectF Cell(float x) const { return SplitView::Cell(x, 0.0f); }
    constexpr RectF Sub(float x, float w) const { return SplitView::Sub(x, 0, w, 1); }

};

struct SplitViewV : public SplitView {
    constexpr SplitViewV() : SplitView() {}
    constexpr SplitViewV(const SplitViewV& rOther) = default;
    constexpr SplitViewV(const RectF& rRect, int32 splitParam)
        : SplitView(rRect, Size{1, splitParam}) {}
    constexpr SplitViewV(const RectF& rRect, float splitParam)
        : SplitView(rRect, SizeF{1, splitParam}) {}

    constexpr RectF Cell(int32 y) const { return SplitView::Cell(0, y); }
    constexpr RectF Cell(float y) const { return SplitView::Cell(0.0f, y); }
    constexpr RectF Sub(float y, float h) const { return SplitView::Sub(0, y, 1, h); }

};

}  // namespace G