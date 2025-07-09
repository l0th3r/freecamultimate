#pragma once
#include <Windows.h>

namespace freecamultimate::backend::dx11
{
    /// Initialise le hook de la fonction IDXGISwapChain::Present().
    bool HookPresent();

    /// Supprime le hook.
    void UnhookPresent();
}