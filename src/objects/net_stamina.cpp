#include "net_stamina.hpp"

NetStamina::NetStamina(uintptr_t stackAddr, uintptr_t offsetGameToBaseAddress)
{
    std::vector<DWORD> pointsOffsets{0x18, 0x110, 0xF70, 0x90, 0x94, 0x18, 0x4D0};
    uintptr_t *baseAddress = reinterpret_cast<uintptr_t *>(stackAddr + offsetGameToBaseAddress);

    if (!baseAddress || !(*baseAddress))
    {
        std::cerr << "Failed to read base address" << std::endl;
        this->netStaminaAddr = 0;
        return;
    }

    uintptr_t currentAddr = *baseAddress;
    for (auto offset : pointsOffsets)
    {
        uintptr_t *nextAddr = reinterpret_cast<uintptr_t *>(currentAddr + offset);
        if (!nextAddr || !(*nextAddr))
        {
            std::cerr << "Failed to resolve player pointer chain at offset: " << std::hex << offset << std::endl;
            this->netStaminaAddr = 0;
            return;
        }
        currentAddr = *nextAddr;
    }

    if (currentAddr < 0x1000) // Validação para endereços inválidos
    {
        std::cerr << "Invalid Final Player Address: " << std::hex << currentAddr << std::endl;
        this->netStaminaAddr = 0;
        return;
    }

    this->netStaminaAddr = currentAddr;
    std::cout << "NetStamina Address resolved: " << std::hex << this->netStaminaAddr << std::endl;
}

void NetStamina::setValue(float newValue)
{
    if (this->netStaminaAddr != 0)
    {
        *(float *)(this->netStaminaAddr + 0x4C) = newValue;
    }
    else
    {
        std::cerr << "Player address is invalid. Cannot set value." << std::endl;
    }
}

int NetStamina::getValue()
{
    if (this->netStaminaAddr != 0)
    {
        try
        {
            uintptr_t valueAddr = this->netStaminaAddr + 0x4C;
            int value = *(int *)(valueAddr); // Lê o valor
            std::cout << "NetStamina current value: " << value << std::endl;
            return value;
        }
        catch (...)
        {
            std::cerr << "Failed to get value at address. " << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "NetStamina address is invalid. Cannot get value." << std::endl;
        return 0;
    }
}