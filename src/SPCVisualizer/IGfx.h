#pragma once

#include "GTypes.h"

#include <memory>

namespace G {

    class IRender;
    class IElem;
    class IFillRect;

class IGfx {
  public:
    virtual ~IGfx() {}

    virtual std::unique_ptr<IRender> CreateRender() = 0;
    virtual std::unique_ptr<IFillRect> CreateFillRect(const Color& rColor) = 0;

  protected:
    IGfx(){};
};
} // namespace G