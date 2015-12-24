#pragma once

#include "DIntf.h"

class DCore
{
public:
    
    DCore();
    ~DCore();

    DCore(const DCore&) = delete;
    DCore& operator=(const DCore&) = delete;
    
    bool Init();
    void Release();

private:

    bool m_init = false;
};