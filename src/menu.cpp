#include "menu.hpp"
#include <demoncore/hooks/hooks.h>
#include <demoncore/utils/utils.h>
#include <demoncore/menu/menu.h>
#include <MinHook.h>

void App::Menu::Create()
{
    U::SetRenderingBackend(OPENGL);
    MH_Initialize();
    H::Init();
}