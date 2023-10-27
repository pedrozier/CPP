#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

class Render
{
public:
    Render(HWND hwnd, int width, int height);
    ~Render();

    void SetClearColor(float r, float g, float b, float a);
    void RenderFrame();

private:
    HWND hwnd;
    int width;
    int height;

    ID3D11Device *pDevice;
    ID3D11DeviceContext *pContext;
    IDXGISwapChain *pSwapChain;
    ID3D11RenderTargetView *pRenderTargetView;

    DirectX::XMFLOAT4 clearColor;
};
