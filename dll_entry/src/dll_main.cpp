#include <Windows.h>
#include <thread>

#include <MinHook.h>

DWORD WINAPI InitThread(LPVOID)
{
    // Ici on pourra appeler le hook, le système ImGui, etc.
    //MessageBoxA(nullptr, "FreecamUltimate DLL injectée avec succès.", "DLL", MB_OK);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    }
    return TRUE;
}
