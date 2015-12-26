#include "Visualizer.h"

#include "ISolidBox.h"
#include "IRender.h"
#include "SplitView.h"

using namespace std;
using namespace G;

Visualizer::Visualizer(G::IGfx& rGfx) : m_rGfx(rGfx) {
    m_pRender = rGfx.CreateRender();
    m_pRender->SetRenderFrameCallback([this] { RenderFrame(); });
}

void Visualizer::RenderFrame() {
    SplitView whole(RectF{-1,-1,1,1});

    SplitViewV grid(whole, 2);

    m_rGfx.FillRect(grid.Cell(0), { 0,200,100 });
    m_rGfx.FillRect(grid.Cell(1), { 100,200,40 });
}
