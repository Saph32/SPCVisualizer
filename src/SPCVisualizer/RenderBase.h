#pragma once

#include "IRender.h"

#include <mutex>

namespace G
{
    class RenderBase : public IRender
    {
    public:
        virtual ~RenderBase() override {}

        virtual void SetRenderFrameCallback(RenderFrameCbFn fnCallback) override {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_renderFrameCb = fnCallback;
        };

    protected:
        RenderBase() {}

        std::mutex m_mutex;
        RenderFrameCbFn m_renderFrameCb;
    };
} // namespace G