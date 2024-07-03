#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <stdio.h>

// Direct3D 11 デバイスとスワップチェーンを初期化する関数
bool InitializeD3D11(HWND hwnd, ID3D11Device** device, IDXGISwapChain** swapChain)
{
    DXGI_SWAP_CHAIN_DESC scd = {0};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0,
                                               D3D11_SDK_VERSION, &scd, swapChain, device, &featureLevel, NULL);

    return SUCCEEDED(hr);
}

void SetFullscreen(IDXGISwapChain* swapChain, BOOL fullscreen)
{
    HRESULT hr = swapChain->SetFullscreenState(fullscreen, NULL);
    if (SUCCEEDED(hr))
    {
        printf("fullscreen success\n");
    }
    else
    {
        printf("fullscreen falnd\n");
    }
}

int main()
{
    HWND hwnd = NULL;
    while ((hwnd = FindWindowW(NULL, L"ドルウェブ")) == NULL)
    {
        Sleep(100);
    }

    ID3D11Device* device = nullptr;
    IDXGISwapChain* swapChain = nullptr;

    if (!InitializeD3D11(hwnd, &device, &swapChain))
    {
        printf("D3D11の初期化に失敗しました。\n");
        return 0;
    }

    Sleep(300);
    // フルスクリーンに切り替える
    SetFullscreen(swapChain, TRUE);

    // 後片付け
    if (swapChain) swapChain->Release();
    if (device) device->Release();

    return 0;
}
