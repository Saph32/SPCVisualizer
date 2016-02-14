#pragma once

#include "IGfx.h"
#include "IRender.h"
#include "VolMeter.h"
#include "Light.h"
#include "Env.h"

#include <vector>

class Visualizer final
{
public:

    Visualizer(G::IGfx& rGfx);
    ~Visualizer();
    Visualizer(const Visualizer&) = delete;
    Visualizer& operator=(const Visualizer&) = delete;

    void RenderFrame();

private:

    G::IGfx& m_rGfx;

    bool m_init = false;

    std::unique_ptr<G::IRender> m_pRender;

    std::unique_ptr<G::VolMeter> m_pVolL;
    std::unique_ptr<G::VolMeter> m_pVolR;

    std::vector<std::unique_ptr<G::Light>>  m_vecKeyOn;
    std::vector<std::unique_ptr<G::Env>>    m_vecEnv;
};