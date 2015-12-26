#pragma once

#include "GTypes.h"

namespace G {
class IElem {
  public:
    virtual ~IElem() {}

    virtual void Draw() = 0;

  protected:
    IElem() {}
};
} // namespace G