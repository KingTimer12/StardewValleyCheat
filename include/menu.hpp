#pragma once

#include <demoncore/application.h>

namespace App
{
    class Menu
    {
    private:
        Demoncore::Application &app;

    public:
        Menu() : app(Demoncore::Application::GetInstance())
        {
            app.dispatcher.sink<Demoncore::LayerEvent::Attach>().connect<&Menu::Create>(*this);
        }

        void Create();
    };
}