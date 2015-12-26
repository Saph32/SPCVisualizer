#include "Visualizer.h"

#include "IFillRect.h"
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

    SplitView grid(whole, Size{2, 2});

    Color c = { 255,255,255 };

    auto pBox = m_rGfx.CreateFillRect(grid.Cell(1, 1), c);

    pBox->Draw();
}
