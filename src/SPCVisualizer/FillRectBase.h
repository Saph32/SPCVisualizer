#pragma once

#include "IFillRect.h"

namespace G
{
    class FillRectBase : public IFillRect
    {
    public:
        virtual ~FillRectBase() override {}

        virtual Color GetColor() { return m_color; }
        virtual void SetColor(const Color& rColor) { m_color = rColor; }

    protected:
        FillRectBase(const Color& rColor) : m_color(rColor){};

        Color m_color;
    };
} // namespace G