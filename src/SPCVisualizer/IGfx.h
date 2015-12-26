#pragma once

#include "GTypes.h"

#include <memory>

namespace G {

    class IRender;
    class IElem;
    class ISolidBox;

class IGfx {
  public:
    virtual ~IGfx() {}

    virtual std::unique_ptr<IRender> CreateRender() = 0;
    virtual std::unique_ptr<ISolidBox> CreateSolidBox(const RectF& rRect, const Color& rColor) = 0;

    virtual void FillRect(const RectF& rRect, const Color& rColor) = 0;

  protected:
    IGfx(){};
};
} // namespace G