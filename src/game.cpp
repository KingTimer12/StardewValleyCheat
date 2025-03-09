#include <demoncore/application.h>
#include "game.hpp"
#include "thread.hpp"

std::shared_ptr<PlayerObj> App::Game::player;
std::shared_ptr<PlayerObj> App::Game::get_player()
{
    return player;
}

void App::Game::Setup()
{
    Process process = GetProcess().value();
    Pid *pid = &process.pid;
    HANDLE hProcHandle = NULL;

    LOG_INFO(("PID founded: " + to_string(*pid)).c_str());
    LOG_INFO("Grabbing handle");
    hProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)*pid);
    if (hProcHandle == INVALID_HANDLE_VALUE || hProcHandle == NULL)
    {
        LOG_ERROR("Failed to open process -- invalid handle");
        LOG_ERROR("Error code: " + to_string(GetLastError()));
        return;
    }

    uintptr_t pointerBaseAddress = GetThreadStack(0, GetCurrentProcess(), pid);
    uintptr_t offsetGameToBaseAddress = -0x00000E30;

    player = std::make_shared<PlayerObj>(PlayerObj(pointerBaseAddress, offsetGameToBaseAddress));
}