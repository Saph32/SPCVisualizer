#define _USE_MATH_DEFINES
#include <cmath>

#include "VolMeter.h"



void G::VolMeter::Draw()
{
    if (m_maxVol == 0) { return; }
    if (m_rect.IsEmpty()) { return; }

    float whole = m_rect.Width();

    double ratio = m_vol / m_maxVol;
    ratio = sqrt(ratio);

    float mid = (float)(whole * ratio);
    float prevMid = m_prevRatio * whole;

    if (mid > prevMid)
    {
        m_rGfx.FillRect({ m_rect.l, m_rect.t, m_rect.l + mid, m_rect.b }, { 255,255,255 });
        m_rGfx.FillRect({ m_rect.l + mid, m_rect.t, m_rect.r, m_rect.b }, { 0,0,0 });
    }
    else
    {
        m_rGfx.FillRect({ m_rect.l, m_rect.t, m_rect.l + mid, m_rect.b }, { 255,255,255 });
        m_rGfx.FillRect({ m_rect.l + mid, m_rect.t, m_rect.l + prevMid, m_rect.b }, { 127,127,127 });
        m_rGfx.FillRect({ m_rect.l + prevMid, m_rect.t, m_rect.r, m_rect.b }, { 0,0,0 });
    }

    m_prevRatio = (float)ratio;
}
