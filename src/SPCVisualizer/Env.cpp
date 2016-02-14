#include "Env.h"

using namespace std;
using namespace G;

void G::Env::Draw() {
    
    G::Color color;

    switch (m_mode)
    {
    case EnvMode::EnvModeAttack:  color = { 255,0,  0 }; break;
    case EnvMode::EnvModeDecay:   color = { 255,255,0 }; break;
    case EnvMode::EnvModeSustain: color = { 0,  255,0 }; break;
    case EnvMode::EnvModeRelease: color = { 0,  0,  255 }; break;
    }

    m_rGfx.FillRect(m_rect, color);
}
