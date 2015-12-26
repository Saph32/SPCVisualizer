#pragma once

#include "DIntf.h"
#include "DRender.h"

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>

#include "unique_handle.h"

class DCore final {
  public:
    typedef std::function<bool()> RenderCbFn;

    DCore();
    ~DCore();

    DCore(const DCore&) = delete;
    DCore& operator=(const DCore&) = delete;

    bool Init();
    void Release();

    void AttachRender(DRender& rRender);
    void DetechRender(DRender&);

    void DrawFillRect(const G::RectF& rRect, const G::Color rColor);

  private:
    struct FlatVertex {
        float    x;
        float    y;
        float    z;
        DirectX::XMFLOAT4 color;
    };

    std::mutex m_mutex;

    bool m_init = false;

    DXGISwapChainPtr         m_pSwapChain  = nullptr;
    D3D11DevicePtr           m_pDevice     = nullptr;
    D3D11DeviceContextPtr    m_pDevCon     = nullptr;
    D3D11RenderTargetViewPtr m_pBackBuffer = nullptr;

    std::thread m_thread;
    RenderCbFn  m_renderCb;

    std::atomic<bool> m_wtInitSuccess;
    std::atomic<bool> m_wtTerminate;

    unique_handle m_wtInitDoneEvent;
    unique_handle m_wtTerminateEvent;

    bool m_classRegistered = false;
    HWND m_hWnd            = NULL;

    DRender* m_pRender = nullptr;

    D3D11PixelShaderPtr  m_pFlat2DPS = nullptr;
    D3D11VertexShaderPtr m_pFlat2DVS = nullptr;

    D3D11BufferPtr       m_pFlatVertexBuf = nullptr;

    D3D11InputLayoutPtr m_pInputLayout   = nullptr;

    static LRESULT CALLBACK WindowProcProxy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    void WorkerThreadProc();

    bool InitD3D();
    void CleanupD3D();
    void RenderFrame();
};