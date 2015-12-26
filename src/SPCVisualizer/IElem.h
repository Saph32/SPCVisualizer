#pragma once

#include "GTypes.h"

namespace G {
class IElem {
  public:
    virtual ~IElem() {}

    virtual void Draw(const RectF& rRect) = 0;

  protected:
    IElem() {}
};
} // namespace G