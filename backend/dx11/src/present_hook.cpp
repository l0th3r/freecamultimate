#include "present_hook.hpp"

#include <MinHook.h>
#include <d3d11.h>
#include <dxgi.h>
#include <cstdio>

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#pragma comment(lib, "d3d11.lib")

namespace freecam::backend::dx11
{
    using PresentFn = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT);
    static PresentFn originalPresent = nullptr;

    static bool g_ImGuiInitialized = false;
    static ID3D11Device* g_Device = nullptr;
    static ID3D11DeviceContext* g_Context = nullptr;
    static HWND g_hWnd = nullptr;

    HRESULT WINAPI MyPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
    {
        if (!g_ImGuiInitialized)
        {
            if (FAILED(swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_Device)))
                return originalPresent(swapChain, syncInterval, flags);

            g_Device->GetImmediateContext(&g_Context);

            DXGI_SWAP_CHAIN_DESC desc;
            swapChain->GetDesc(&desc);
            g_hWnd = desc.OutputWindow;

            ImGui::CreateContext();
            ImGui_ImplWin32_Init(g_hWnd);
            ImGui_ImplDX11_Init(g_Device, g_Context);

            g_ImGuiInitialized = true;
            OutputDebugStringA("[Freecam] ImGui initialisé dans MyPresent.\n");
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Freecam Ultimate");
        ImGui::Text("Hook Present() fonctionne !");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        return originalPresent(swapChain, syncInterval, flags);
    }

    bool HookPresent(IDXGISwapChain* realSwapChain)
    {
        static bool alreadyHooked = false;
        if (alreadyHooked || !realSwapChain)
            return alreadyHooked;

        void** vtable = *reinterpret_cast<void***>(realSwapChain);
        void* presentAddr = vtable[8]; // IDXGISwapChain::Present

        if (MH_Initialize() != MH_OK)
        {
            OutputDebugStringA("[Freecam] MH_Initialize() a échoué.\n");
            return false;
        }

        if (MH_CreateHook(presentAddr, &MyPresent, reinterpret_cast<void**>(&originalPresent)) != MH_OK)
        {
            OutputDebugStringA("[Freecam] MH_CreateHook() a échoué.\n");
            return false;
        }

        if (MH_EnableHook(presentAddr) != MH_OK)
        {
            OutputDebugStringA("[Freecam] MH_EnableHook() a échoué.\n");
            return false;
        }

        alreadyHooked = true;
        OutputDebugStringA("[Freecam] Hook de Present() installé.\n");
        return true;
    }

    void UnhookPresent()
    {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
        OutputDebugStringA("[Freecam] Hooks désinstallés.\n");
    }
}
