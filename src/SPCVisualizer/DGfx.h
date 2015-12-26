#pragma once

#include "IGfx.h"
#include "DIntf.h"
#include "DRender.h"
#include "DFillRect.h"

class DGfx : public G::IGfx
{
public:

    DGfx(DCore& rCore) : m_rCore(rCore) {}
    virtual ~DGfx() {}

    virtual std::unique_ptr<G::IRender> CreateRender() override;
    virtual std::unique_ptr<G::IFillRect> CreateFillRect(const G::Color& rColor) override;

private:

    DCore& m_rCore;
};