#include "immortal.hpp"
#include "game.hpp"

#include <demoncore/feature.h>

void App::Immortal::Register()
{
    auto features = Demoncore::Features::GetInstance();
    features->Push(new Demoncore::Feature("Immortal"));
}

void App::Immortal::Update()
{
    if (Demoncore::Features::GetInstance()->Get("Immortal")->enabled)
        Game::get_player()->setHeath(125);
}