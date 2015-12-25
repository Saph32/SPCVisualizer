#include "DCore.h"

#pragma comment(lib, "d3d11.lib")

DCore::DCore() {}

DCore::~DCore() {
    if (m_init) {
        Release();
    }
}

bool DCore::Init() {
    if (m_init) {
        return true;
    }

    m_init = true;
    return m_init;
}

void DCore::Release() {
    m_init = false;
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
    default: break;
    }

    return ::DefWindowProc(hWnd, message, wParam, lParam);
}
