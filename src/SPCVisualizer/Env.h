#pragma once

#include "IElem.h"
#include "IGfx.h"

namespace G {

    class Env : public IElem {
    public:
        Env(IGfx& rGfx) : m_rGfx(rGfx) {}

        // Interface implementation : IElem
        virtual void Draw() override;

        // Other methods
        void SetRect(const RectF& rRect) { m_rect = rRect; }
        void SetMode(EnvMode mode) { m_mode = mode; }

        RectF GetRect() const { return m_rect; }

    private:
        IGfx& m_rGfx;

        RectF m_rect = {};
        EnvMode m_mode = EnvModeAttack;
    };
}  // namespace G