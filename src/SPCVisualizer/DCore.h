#pragma once

#include "DIntf.h"

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>

#include "unique_handle.h"

class DCore {
  public:
    typedef std::function<bool()> RenderCbFn;

    DCore();
    ~DCore();

    DCore(const DCore &) = delete;
    DCore &operator=(const DCore &) = delete;

    bool Init();
    void Release();

  private:
    std::mutex m_mutex;

    bool m_init = false;

    DXGISwapChainPtr      m_pSwapChain = nullptr;
    D3D11DevicePtr        m_pDevice = nullptr;
    D3D11DeviceContextPtr m_pDevCon = nullptr;
    D3D11RenderTargetViewPtr m_pBackBuffer = nullptr;

    std::thread m_thread;
    RenderCbFn  m_renderCb;

    std::atomic<bool> m_wtInitSuccess;
    std::atomic<bool> m_wtTerminate;

    unique_handle m_wtInitDoneEvent;
    unique_handle m_wtTerminateEvent;

    bool m_classRegistered = false;
    HWND m_hWnd = NULL;

    static LRESULT CALLBACK WindowProcProxy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    void WorkerThreadProc();

    bool InitD3D();
    void CleanupD3D();
    void RenderFrame();
};