#pragma once

#include "components.hpp"

class PlayerObj
{
private:
    uintptr_t playerAddr;
    HANDLE hProcHandle;
    void setValue(uintptr_t, int);

public:
    PlayerObj(uintptr_t, uintptr_t);
    void setHeath(int);
    void setMaxHealth(int);
    uintptr_t getPlayerAddr();

    template <typename T>
    T getValue(uintptr_t);
};