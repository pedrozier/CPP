#include "headers/Render.h"

#include <d3d11.h>
#include <dxgi.h>

Render::Render(HWND hwnd, int width, int height)
    : hwnd(hwnd), width(width), height(height),
      pDevice(nullptr), pContext(nullptr), pSwapChain(nullptr), pRenderTargetView(nullptr)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0};
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        featureLevels, _countof(featureLevels), D3D11_SDK_VERSION,
        &sd, &pSwapChain, &pDevice, nullptr, &pContext);

    if (FAILED(hr))
    {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    }

    ID3D11Texture2D *pBackBuffer = nullptr;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&pBackBuffer));
    pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
    pBackBuffer->Release();

    pContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);

    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<FLOAT>(width);
    vp.Height = static_cast<FLOAT>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    pContext->RSSetViewports(1, &vp);
}

Render::~Render()
{
    if (pRenderTargetView)
    {
        pRenderTargetView->Release();
        pRenderTargetView = nullptr;
    }

    if (pSwapChain)
    {
        pSwapChain->Release();
        pSwapChain = nullptr;
    }

    if (pContext)
    {
        pContext->Release();
        pContext = nullptr;
    }

    if (pDevice)
    {
        pDevice->Release();
        pDevice = nullptr;
    }
}

void Render::RenderFrame()
{
    float ClearColor[4] = {0.0f, 0.125f, 0.6f, 1.0f};
    pContext->ClearRenderTargetView(pRenderTargetView, ClearColor);

    pSwapChain->Present(0, 0);
}
