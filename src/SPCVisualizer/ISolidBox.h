#pragma once

#include "IElem.h"

namespace G {
class ISolidBox : public IElem {
  public:
    virtual ~ISolidBox() override {}

    virtual RectF GetRect()  = 0;
    virtual Color GetColor() = 0;

    virtual void SetRect(const RectF& rRect)    = 0;
    virtual void SetColor(const Color& rColor) = 0;

  protected:
    ISolidBox() {}
};
}  // namespace G