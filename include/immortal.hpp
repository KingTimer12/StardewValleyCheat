#pragma once
#include <demoncore/application.h>

namespace App
{
    class Immortal
    {
    private:
        Demoncore::Application &app;

    public:
        Immortal() : app(Demoncore::Application::GetInstance())
        {
            app.dispatcher.sink<Demoncore::LayerEvent::Attach>().connect<&Immortal::Register>(*this);
            app.dispatcher.sink<Demoncore::LayerEvent::Update>().connect<&Immortal::Update>(*this);
        }

        void Register();
        void Update();
    };
}