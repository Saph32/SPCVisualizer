#pragma once

#include "IFillRect.h"
#include "DIntf.h"

class DFillRect : public G::IFillRect
{
public:
    DFillRect(DCore& rCore, const G::Color& rColor) : m_color(rColor), m_rCore(rCore) {}
    virtual ~DFillRect() override {}

    // Interface implementation: IFillRect
    virtual G::Color GetColor() override { return m_color; }
    virtual void SetColor(const G::Color& rColor) override { m_color = rColor; }

    // Interface implementation: IElem
    virtual void Draw(const G::RectF& rRect) override;

private:
    DCore& m_rCore;

    G::Color m_color;
};