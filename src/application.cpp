#include <demoncore/demoncore.h>
#include <demoncore/hooks/hooks.h>
#include <demoncore/utils/utils.h>
#include <MinHook.h>

#include "menu.hpp"

Demoncore::Application &Demoncore::create_application()
{
    auto &app = Demoncore::Application::GetInstance();

    LAYER(App::Menu);

    return app;
}