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
    std::vector<DWORD> pointsOffsets{0x18, 0x110, 0xF70, 0x90, 0x94, 0x18, 0x6EC};
    uint64_t baseAddr = NULL;
    ReadProcessMemory(hProcHandle, (LPCVOID)(pointerBaseAddress + offsetGameToBaseAdress), &baseAddr, sizeof(baseAddr), NULL);
    std::cout << "Base Address: " << to_string(baseAddr) << std::endl;
    uint64_t finalAddress = baseAddr;
    for (int i = 0; i < pointsOffsets.size() - 1; i++)
    {
        ReadProcessMemory(hProcHandle, (LPCVOID)(finalAddress + pointsOffsets[i]), &finalAddress, sizeof(finalAddress), NULL);
        std::cout << "Offset: " << to_string(pointsOffsets[i]) << " = " << to_string(finalAddress) << std::endl;
    }
    finalAddress += pointsOffsets[pointsOffsets.size() - 1];
    int newvalue = 20;
    WriteProcessMemory(hProcHandle, (LPVOID)(finalAddress), &newvalue, sizeof(newvalue), NULL);

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
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