#include "thread.hpp"

#include "player_obj.hpp"
#include "net_stamina.hpp"

DWORD WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    FILE *f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    Process process = GetProcess().value();
    Pid *pid = &process.pid;
    HANDLE hProcHandle = NULL;

    std::cout << ("PID founded: " + to_string(*pid)).c_str() << std::endl;
    std::cout << "Grabbing handle" << std::endl;
    hProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)*pid);
    if (hProcHandle == INVALID_HANDLE_VALUE || hProcHandle == NULL)
    {
        std::cerr << "Failed to open process -- invalid handle" << std::endl;
        std::cerr << "Error code: " << GetLastError() << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "Success" << std::endl;
    }

    uintptr_t pointerBaseAddress = GetThreadStack(0, GetCurrentProcess(), pid);
    uintptr_t offsetGameToBaseAddress = -0x00000E30;
    PlayerObj player(pointerBaseAddress, offsetGameToBaseAddress);
    NetStamina netStamina(pointerBaseAddress, offsetGameToBaseAddress);
    // player.setHeath(100);
    // player.setMaxHealth(125);

    bool immortal = false, infiniteStamina = false;

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            immortal = !immortal;
        }
        if (GetAsyncKeyState(VK_F2) & 1)
        {
            infiniteStamina = !infiniteStamina;
        }
        if (immortal)
        {
            player.setHeath(125);
        }
        if (infiniteStamina)
        {
            netStamina.setValue<float>(0x4C, 338);
        }
    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}