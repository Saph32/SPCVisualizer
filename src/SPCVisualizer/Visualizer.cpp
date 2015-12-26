#include "Visualizer.h"
#include "SoundModule.h"
#include "ISolidBox.h"
#include "IRender.h"
#include "SplitView.h"
#include "VolMeter.h"

#include <cmath>
#include <algorithm>

using namespace std;
using namespace G;

extern SoundModule g_oSoundModule;

Visualizer::Visualizer(G::IGfx& rGfx) : m_rGfx(rGfx) {
    m_pRender = rGfx.CreateRender();
    m_pRender->SetRenderFrameCallback([this] { RenderFrame(); });
}

Visualizer::~Visualizer()
{
    m_pRender->SetRenderFrameCallback(nullptr);
}

void Visualizer::RenderFrame() {
    if (!m_init)
    {
        m_pVolL.reset(new VolMeter(m_rGfx));
        m_pVolR.reset(new VolMeter(m_rGfx));

        m_init = true;
    }
    auto state = g_oSoundModule.GetVis();

    SplitView whole(RectF{-1,-1,1,1});

    SplitViewV grid(whole, 2);

    m_pVolL->SetRect(grid.Cell(0));
    m_pVolR->SetRect(grid.Cell(1));

    m_pVolL->SetMaxVol(32768.0f);
    m_pVolR->SetMaxVol(32768.0f);

    auto fnGetMax = [](auto& q) -> int16 {
        int16 maxL = 0;
        for (auto& r : q)
        {
            maxL = max(maxL, (int16)abs(r));
        }
        return maxL;
    };

    float maxL = (float)fnGetMax(state.sampsL);
    float maxR = (float)fnGetMax(state.sampsR);

    m_pVolL->SetVol(maxL);
    m_pVolR->SetVol(maxR);

    m_pVolL->Draw();
    m_pVolR->Draw();
}
