#include "DCore.h"
#include "DSolidBox.h"
#include "DGfx.h"

using namespace std;
using namespace G;
using namespace DirectX;

DGfx::DGfx() : m_pCore(new DCore()) {}

DGfx::~DGfx()
{
    if (m_init) {
        Release();
    }
}

std::unique_ptr<G::IRender> DGfx::CreateRender() {
    return make_unique<DRender>(*m_pCore);
}

std::unique_ptr<G::ISolidBox> DGfx::CreateSolidBox(const G::RectF& rRect, const G::Color& rColor) {
    return make_unique<DSolidBox>(*m_pCore, rRect, rColor);
}

void DGfx::FillRect(const G::RectF & rRect, const G::Color & rColor)
{
    m_pCore->DrawFillRect(rRect, rColor);
}

bool DGfx::Init() {
    m_init = m_pCore->Init();
    return m_init;
}

void DGfx::Release() {
    m_init = false;
    m_pCore->Release();
}
