#pragma once

#include "components.hpp"

class NetStamina
{
private:
    uintptr_t netStaminaAddr;

public:
    NetStamina(uintptr_t, uintptr_t);
    void setValue(float newValue);
    int getValue();
};