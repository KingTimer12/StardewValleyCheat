#pragma once

#include "components.hpp"
#include <demoncore/application.h>

#include "player_obj.hpp"
#include "net_stamina.hpp"

namespace App
{
    class Game
    {
    private:
        Demoncore::Application &app;
        static std::shared_ptr<PlayerObj> player;

    public:
        Game() : app(Demoncore::Application::GetInstance())
        {
            app.dispatcher.sink<Demoncore::LayerEvent::Attach>().connect<&Game::Setup>(*this);
        }

        void Setup();
        static std::shared_ptr<PlayerObj> get_player();
    };
}