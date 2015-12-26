#pragma once

#include "RenderBase.h"
#include "DIntf.h"

class DRender final : public G::RenderBase
{
public:
    DRender(DCore& rCore);
    virtual ~DRender() override;

    // Other methods
    void RenderFrame();

private:
    DCore& m_rCore;
};