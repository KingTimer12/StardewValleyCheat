#pragma once

#include "components.hpp"

class PlayerObj
{
private:
    uint64_t *playerAddr;
    HANDLE hProcHandle;
    void setValue(uint64_t, int);

public:
    PlayerObj(HANDLE hProcHandle, uint64_t, uint64_t);
    void setHeath(int);
    void setMaxHealth(int);
    ~PlayerObj();
};