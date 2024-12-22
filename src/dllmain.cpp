#include "player_obj.hpp"
#include "components.hpp"
#include "thread.hpp"

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

    uint64_t pointerBaseAddress = GetThreadStack(0, hProcHandle, pid);
    uint64_t offsetGameToBaseAdress = -0x00000E30;
    PlayerObj player(hProcHandle, pointerBaseAddress, offsetGameToBaseAdress);
    // player.setHeath(125);
    // player.setMaxHealth(125);

    bool immortal = false;

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
        if (immortal)
        {
            player.setHeath(125);
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