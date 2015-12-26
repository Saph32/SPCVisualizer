#include "DSolidBox.h"
#include "DCore.h"

using namespace std;
using namespace G;
using namespace DirectX;

void DSolidBox::Draw()
{
    m_rCore.DrawFillRect(m_rect, m_color);
}
