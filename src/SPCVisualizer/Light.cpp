#include "Light.h"

using namespace std;
using namespace G;

void G::Light::Draw() {
    if (m_maxVal == 0) {
        return;
    }
    if (m_rect.IsEmpty()) {
        return;
    }

    float ratio = m_val / m_maxVal;

    ratio = ratio * ratio * ratio;

    auto color =
        Color{(uint8)(m_color.r * ratio), (uint8)(m_color.g * ratio), (uint8)(m_color.b * ratio), 255};

    m_rGfx.FillRect(m_rect, color);
}
