#pragma once

#include "components.hpp"
#include "net_stamina.hpp"

class PlayerObj
{
private:
    uintptr_t playerAddr;
    NetStamina netStamina;
    HANDLE hProcHandle;
    void setValue(uintptr_t, int);

public:
    PlayerObj(uintptr_t, uintptr_t);
    void setHeath(int);
    void setMaxHealth(int);
    uintptr_t getPlayerAddr();
    NetStamina getNetStamina();

    template <typename T>
    T getValue(uintptr_t);
};