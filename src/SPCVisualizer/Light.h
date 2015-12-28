#pragma once

#include "IElem.h"
#include "IGfx.h"

namespace G {

class Light : public IElem {
  public:
    Light(IGfx& rGfx) : m_rGfx(rGfx) {}

    // Interface implementation : IElem
    virtual void Draw() override;

    // Other methods
    void SetRect(const RectF& rRect) { m_rect = rRect; }
    void SetVal(float val) { m_val = val; }
    void SetMaxVal(float val) { m_maxVal = val; }
    void SetColor(const Color& rColor) { m_color = rColor; }

    RectF GetRect() const { return m_rect; }

  private:
    IGfx& m_rGfx;

    RectF m_rect   = {};
    float m_val    = 0;
    float m_maxVal = 1;
    Color m_color = { 255,255,255,255 };
};
}  // namespace G