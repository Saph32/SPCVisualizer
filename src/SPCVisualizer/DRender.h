#pragma once

#include "IRender.h"
#include "DIntf.h"

#include <mutex>

class DRender final : public G::IRender
{
public:
    DRender(DCore& rCore);
    virtual ~DRender() override;

    // Interface implementation
    virtual void SetRenderFrameCallback(RenderFrameCbFn fnCallback) override {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_renderFrameCb = fnCallback;
    };

    // Other methods
    void RenderFrame();

private:
    DCore& m_rCore;

    std::mutex m_mutex;
    RenderFrameCbFn m_renderFrameCb;
};