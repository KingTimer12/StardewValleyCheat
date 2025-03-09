#include <demoncore/demoncore.h>
#include <demoncore/hooks/hooks.h>
#include <demoncore/utils/utils.h>
#include <MinHook.h>

#include "immortal.hpp"

#include "game.hpp"
#include "menu.hpp"

Demoncore::Application &Demoncore::create_application()
{
    auto &app = Demoncore::Application::GetInstance();

    LAYER(App::Game);
    LAYER(App::Immortal);
    LAYER(App::Menu);

    return app;
}