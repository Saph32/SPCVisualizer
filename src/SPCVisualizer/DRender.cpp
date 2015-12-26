#include "DRender.h"
#include "DCore.h"

using namespace std;
using namespace G;
using namespace DirectX;

DRender::DRender(DCore & rCore)
    : m_rCore(rCore)
{
    rCore.AttachRender(*this);
}

DRender::~DRender()
{
    m_rCore.DetechRender(*this);
}

void DRender::RenderFrame()
{
    lock_guard<mutex> lock(m_mutex);

    if (m_renderFrameCb)
    {
        m_renderFrameCb();
    }
}
