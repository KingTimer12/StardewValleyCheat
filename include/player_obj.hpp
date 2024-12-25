#pragma once

#include "components.hpp"
#include "abstract_obj.hpp"

class PlayerObj : public AbstractObj
{
private:
    HANDLE hProcHandle;

public:
    PlayerObj(uintptr_t, uintptr_t);
    void setHeath(int);
    void setMaxHealth(int);
};