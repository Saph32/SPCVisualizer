#include "DCore.h"

#pragma comment (lib, "d3d11.lib")

DCore::DCore()
{
}

DCore::~DCore()
{
    if (m_init)
    {
        Release();
    }
}

bool DCore::Init()
{
    m_init = true;
    return m_init;
}

void DCore::Release()
{
    m_init = false;
}
