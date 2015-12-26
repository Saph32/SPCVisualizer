#pragma once

#include "GTypes.h"

#include <functional>

namespace G
{
    class IRender
    {
    public:
        typedef std::function<void()> RenderFrameCbFn;

        virtual ~IRender() {};

        virtual void SetRenderFrameCallback(RenderFrameCbFn fnCallback) = 0;

    protected:
        IRender() {};

    private:
    };
} // namespace G