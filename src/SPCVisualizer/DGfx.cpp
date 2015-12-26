#include "DGfx.h"
#include "DIntf.h"

using namespace std;
using namespace G;
using namespace DirectX;

std::unique_ptr<G::IRender> DGfx::CreateRender()
{
    return make_unique<DRender>(m_rCore);
}

std::unique_ptr<G::IFillRect> DGfx::CreateFillRect(const G::Color & rColor)
{
    return make_unique<DFillRect>(m_rCore, rColor);
}
