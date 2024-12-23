#pragma once

#include "player_obj.hpp"

class NetStamina
{
private:
    uintptr_t netStaminaAddr;

public:
    NetStamina(PlayerObj player);
    void setValue(int newValue);
    int getValue();
};