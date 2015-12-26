#pragma once

#include "IElem.h"
#include "IGfx.h"

namespace G {
class VolMeter : public IElem {
  public:
      VolMeter(IGfx& rGfx) : m_rGfx(rGfx) {}

      // Interface implementation : IElem
      virtual void Draw() override;

      // Other methods
      void SetRect(const RectF& rRect) { m_rect = rRect; }
      void SetVol(float vol) { m_vol = vol; }
      void SetMaxVol(float vol) { m_maxVol = vol; }

      RectF GetRect() const { return m_rect; }

private:
    IGfx& m_rGfx;

    RectF m_rect = {};
    float m_vol = 0;
    float m_maxVol = 1;
    float m_prevRatio = 0;
};
}