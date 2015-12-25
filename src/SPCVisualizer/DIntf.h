#pragma once

#include <atlbase.h>
#include <d3d11.h>
#include <windows.h>

#include "IGfx.h"

#include <memory>

class DCore;

typedef CComPtr<IDXGISwapChain>      DXGISwapChainPtr;
typedef CComPtr<ID3D11Device>        D3D11DevicePtr;
typedef CComPtr<ID3D11DeviceContext> D3D11DeviceContextPtr;