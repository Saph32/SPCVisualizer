#include "DCore.h"

#include "auto.h"

#include "Flat2DPS.h"
#include "Flat2DVS.h"

#include "SimpleMath.h"

#pragma comment(lib, "d3d11.lib")

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const wchar_t* gc_className = L"WindowClassD";

DCore::DCore() {}

DCore::~DCore() {
    if (m_init) {
        Release();
    }
}

bool DCore::Init() {
    if (!m_init) {
        m_wtInitDoneEvent.reset(::CreateEvent(NULL, FALSE, FALSE, NULL));
        m_wtTerminateEvent.reset(::CreateEvent(NULL, FALSE, FALSE, NULL));

        if (!m_wtInitDoneEvent || !m_wtTerminateEvent) {
            return false;
        }

        m_wtInitSuccess = false;
        m_thread        = thread(&DCore::WorkerThreadProc, this);

        auto returnVal = ::WaitForSingleObject(m_wtInitDoneEvent.get(), INFINITE);
        if (returnVal != WAIT_OBJECT_0) {
            return false;
        }

        if (!m_wtInitSuccess) {
            return false;
        }

        m_init = true;
    }

    Auto(if (!m_init) { Release(); });

    return m_init;
}

void DCore::Release() {
    m_init = false;

    m_wtTerminate = true;
    ::SetEvent(m_wtTerminateEvent.get());

    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void DCore::AttachRender(DRender& rRender) {
    lock_guard<mutex> lock(m_mutex);
    m_pRender = &rRender;
}

void DCore::DetechRender(DRender&) {
    lock_guard<mutex> lock(m_mutex);
    m_pRender = nullptr;
}

LRESULT DCore::WindowProcProxy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    DCore* pThis = nullptr;

    if (message == WM_NCCREATE) {
        pThis = reinterpret_cast<DCore*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
        ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<DCore*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    return pThis->WindowProc(hWnd, message, wParam, lParam);
}

LRESULT DCore::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    } break;
    default: break;
    }

    return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void DCore::WorkerThreadProc() {
    m_wtInitSuccess = false;

    Auto(if (!m_wtInitSuccess) { ::SetEvent(m_wtInitDoneEvent.get()); });

    if (!InitD3D()) {
        return;
    }

    Auto(CleanupD3D());

    m_wtInitSuccess = true;
    ::SetEvent(m_wtInitDoneEvent.get());

    while (!m_wtTerminate) {
        MSG msg = {};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                m_wtTerminate = true;
                return;
            }
        }

        RenderFrame();
    }
}

bool DCore::InitD3D() {
    bool success = false;

    Auto(if (!success) { CleanupD3D(); });

    m_classRegistered = false;
    WNDCLASSEX wc     = {};

    wc.cbSize        = sizeof(wc);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = &DCore::WindowProcProxy;
    wc.lpszClassName = gc_className;

    if (!::RegisterClassEx(&wc)) {
        return false;
    }

    m_hWnd = ::CreateWindowEx(NULL,
                              gc_className,         // name of the window class
                              L"SPC Visualizer",    // title of the window
                              WS_OVERLAPPEDWINDOW,  // window style
                              300,                  // x-position of the window
                              300,                  // y-position of the window
                              1280,                 // width of the window
                              720,                  // height of the window
                              NULL,                 // we have no parent window, NULL
                              NULL,                 // we aren't using menus, NULL
                              NULL,                 // application handle
                              NULL);                // used with multiple windows, NULL

    if (!m_hWnd) {
        return false;
    }

    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount          = 1;
    scd.BufferDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow         = m_hWnd;
    scd.SampleDesc.Count     = 1;
    scd.Windowed             = true;

    UINT createFlags = 0;

#ifdef _DEBUG
    createFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

    auto hResult = D3D11CreateDeviceAndSwapChain(nullptr,
                                                 D3D_DRIVER_TYPE_HARDWARE,
                                                 nullptr,
                                                 createFlags,
                                                 nullptr,
                                                 0,
                                                 D3D11_SDK_VERSION,
                                                 &scd,
                                                 &m_pSwapChain,
                                                 &m_pDevice,
                                                 nullptr,
                                                 &m_pDevCon);

    if (!SUCCEEDED(hResult)) {
        return false;
    }

    D3D11Texture2DPtr pBackBuffer = nullptr;
    hResult = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (!SUCCEEDED(hResult)) {
        return false;
    }

    hResult = m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pBackBuffer);

    if (!SUCCEEDED(hResult)) {
        return false;
    }

    ID3D11RenderTargetView* aRenderTargets[] = {m_pBackBuffer};
    m_pDevCon->OMSetRenderTargets(1, aRenderTargets, nullptr);

    D3D11_VIEWPORT viewport = {};

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width    = 1280;
    viewport.Height   = 720;

    m_pDevCon->RSSetViewports(1, &viewport);

    hResult = m_pDevice->CreatePixelShader(g_flat2DPS, sizeof(g_flat2DPS), nullptr, &m_pFlat2DPS);
    if (!SUCCEEDED(hResult)) {
        return false;
    }

    hResult = m_pDevice->CreateVertexShader(g_flat2DVS, sizeof(g_flat2DVS), nullptr, &m_pFlat2DVS);
    if (!SUCCEEDED(hResult)) {
        return false;
    }

    D3D11_BUFFER_DESC bd = {};

    bd.Usage          = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth      = sizeof(FlatVertex) * 4;
    bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hResult = m_pDevice->CreateBuffer(&bd, nullptr, &m_pFlatVertexBuf);
    if (!SUCCEEDED(hResult)) {
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC iedFlat[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    m_pDevice->CreateInputLayout(iedFlat, 2, g_flat2DVS, sizeof(g_flat2DVS), &m_pInputLayout);
    m_pDevCon->IASetInputLayout(m_pInputLayout);

    ::ShowWindow(m_hWnd, SW_SHOW);

    success = true;
    return success;
}

void DCore::CleanupD3D() {
    if (m_hWnd) {
        ::DestroyWindow(m_hWnd);
        m_hWnd = NULL;
    }

    if (m_classRegistered) {
        ::UnregisterClass(gc_className, NULL);
        m_classRegistered = false;
    }
}

void DCore::RenderFrame() {
    lock_guard<mutex> lock(m_mutex);

    XMFLOAT4 bkgColor(0.1f, 0.2f, 0.3f, 1.0f);
    m_pDevCon->ClearRenderTargetView(m_pBackBuffer, (FLOAT*)&bkgColor);

    if (m_pRender) {
        m_pRender->RenderFrame();
    }

    m_pSwapChain->Present(0, 0);
}

void DCore::DrawFillRect(const G::RectF& rRect, const G::Color rColor) {
    m_pDevCon->VSSetShader(m_pFlat2DVS, 0, 0);
    m_pDevCon->PSSetShader(m_pFlat2DPS, 0, 0);

    D3D11_MAPPED_SUBRESOURCE ms = {};
    m_pDevCon->Map(m_pFlatVertexBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

    auto color = Color(rColor.r / 255.0f, rColor.g / 255.0f, rColor.b / 255.0f);

    auto pVertices = reinterpret_cast<FlatVertex*>(ms.pData);
    pVertices[0].x = rRect.l;
    pVertices[0].y = -rRect.t;
    pVertices[0].z = 0;

    pVertices[1].x = rRect.r;
    pVertices[1].y = -rRect.t;
    pVertices[1].z = 0;

    pVertices[2].x = rRect.l;
    pVertices[2].y = -rRect.b;
    pVertices[2].z = 0;

    pVertices[3].x = rRect.r;
    pVertices[3].y = -rRect.b;
    pVertices[3].z = 0;

    pVertices[0].color = pVertices[1].color = pVertices[2].color = pVertices[3].color = color;

    m_pDevCon->Unmap(m_pFlatVertexBuf, 0);

    ID3D11Buffer* pVertexBufs[] = { m_pFlatVertexBuf };
    UINT stride = sizeof(FlatVertex);
    UINT offset = 0;
    m_pDevCon->IASetVertexBuffers(0, 1, pVertexBufs, &stride, &offset);

    m_pDevCon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    m_pDevCon->Draw(4, 0);
}
