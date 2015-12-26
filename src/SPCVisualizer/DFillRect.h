#pragma once

#include "FillRectBase.h"
#include "DIntf.h"

class DFillRect : public G::FillRectBase
{
public:
    DFillRect(DCore& rCore, const G::Color& rColor) : FillRectBase(rColor), m_rCore(rCore) {}
    virtual ~DFillRect() override {}

    virtual void Draw(const G::RectF& rRect) override;

private:
    DCore& m_rCore;
};