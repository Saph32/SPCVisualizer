#pragma once

#include "DIntf.h"

#include <mutex>
#include <thread>

class DCore {
  public:
    DCore();
    ~DCore();

    DCore(const DCore &) = delete;
    DCore &operator=(const DCore &) = delete;

    bool Init();
    void Release();

  private:
    std::mutex m_mutex;

    bool m_init = false;

    DXGISwapChainPtr      m_swapChain;
    D3D11DevicePtr        m_device;
    D3D11DeviceContextPtr m_devcon;

    std::thread m_thread;

    static LRESULT CALLBACK WindowProcProxy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};