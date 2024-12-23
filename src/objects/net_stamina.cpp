#include "net_stamina.hpp"

NetStamina::NetStamina(PlayerObj player)
{
    this->netStaminaAddr = *player.getValue<uintptr_t *>(0x4D0);
    std::cout << "NetStamina Address resolved: " << std::hex << this->netStaminaAddr << std::endl;
}

void NetStamina::setValue(int newValue)
{
    if (this->netStaminaAddr)
    {
        *(int *)(this->netStaminaAddr + 0x4C) = newValue;
    }
    else
    {
        std::cerr << "NetStamina address is invalid. Cannot set value." << std::endl;
    }
}

int NetStamina::getValue()
{
    if (this->netStaminaAddr)
    {
        return *(int *)(this->netStaminaAddr + 0x4C);
    }
    else
    {
        std::cerr << "NetStamina address is invalid. Cannot get value." << std::endl;
        return 0;
    }
}