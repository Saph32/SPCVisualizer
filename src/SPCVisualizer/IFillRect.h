#pragma once

#include "IElem.h"

namespace G {
class IFillRect : public IElem {
  public:
      virtual ~IFillRect() override {}

    virtual Color GetColor()                   = 0;
    virtual void SetColor(const Color& rColor) = 0;

  protected:
    IFillRect() {}
};
}  // namespace G