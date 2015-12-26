#pragma once

#include "DIntf.h"
#include "ISolidBox.h"

class DSolidBox : public G::ISolidBox {
  public:
    DSolidBox(DCore& rCore, const G::RectF& rRect, const G::Color& rColor)
        : m_rect(rRect), m_color(rColor), m_rCore(rCore) {}
    virtual ~DSolidBox() override {}

    // Interface implementation: IFillRect
    virtual G::Color GetColor() override { return m_color; }
    virtual G::RectF GetRect() override { return m_rect; }

    virtual void SetColor(const G::Color& rColor) override { m_color = rColor; }
    virtual void SetRect(const G::RectF& rRect) override { m_rect = rRect; }

    // Interface implementation: IElem
    virtual void Draw() override;

  private:
    DCore& m_rCore;

    G::RectF m_rect  = {};
    G::Color m_color = {};
};