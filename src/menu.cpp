#include "menu.hpp"
#include <demoncore/hooks/hooks.h>
#include <demoncore/utils/utils.h>
#include <demoncore/menu/menu.h>
#include <demoncore/feature.h>
#include <MinHook.h>

#include <imgui.h>

void MyCustomRender()
{
    auto features = Demoncore::Features::GetInstance();
    ImGui::Text("Stardew Valley Cheat");
    for (auto feature : features->All())
    {
        ImGui::Checkbox(feature->label, &feature->enabled);
    }
}

void App::Menu::Create()
{
    U::SetRenderingBackend(OPENGL);
    MH_Initialize();

    Demoncore::Menu::SetMenuTitle("Stardew Valley");
    Demoncore::Menu::SetRenderCallback(MyCustomRender);

    H::Init();
}