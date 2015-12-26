#include "DFillRect.h"
#include "DCore.h"

using namespace std;
using namespace G;
using namespace DirectX;

void DFillRect::Draw()
{
    m_rCore.DrawFillRect(m_rect, m_color);
}
