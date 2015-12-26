#pragma once

#include "IGfx.h"
#include "IRender.h"

class Visualizer final
{
public:

    Visualizer(G::IGfx& rGfx);
    Visualizer(const Visualizer&) = delete;
    Visualizer& operator=(const Visualizer&) = delete;

    void RenderFrame();

private:

    G::IGfx& m_rGfx;

    std::unique_ptr<G::IRender> m_pRender;
};