#include "player_obj.hpp"

// Offsets
constexpr uintptr_t OFFSET_HEALTH = 0x6EC;
constexpr uintptr_t OFFSET_MAX_HEALTH = 0x6F0;

PlayerObj::PlayerObj(uintptr_t stackAddr, uintptr_t offsetGameToBaseAddress) : netStamina(0)
{
    std::vector<DWORD> pointsOffsets{0x18, 0x110, 0xF70, 0x90, 0x94, 0x18};
    uintptr_t *baseAddress = reinterpret_cast<uintptr_t *>(stackAddr + offsetGameToBaseAddress);

    if (!baseAddress || !(*baseAddress))
    {
        std::cerr << "Failed to read base address" << std::endl;
        this->playerAddr = 0;
        return;
    }

    uintptr_t currentAddr = *baseAddress;
    for (auto offset : pointsOffsets)
    {
        uintptr_t *nextAddr = reinterpret_cast<uintptr_t *>(currentAddr + offset);
        if (!nextAddr || !(*nextAddr))
        {
            std::cerr << "Failed to resolve player pointer chain at offset: " << std::hex << offset << std::endl;
            this->playerAddr = 0;
            return;
        }
        currentAddr = *nextAddr;
    }

    if (currentAddr < 0x1000) // Validação para endereços inválidos
    {
        std::cerr << "Invalid Final Player Address: " << std::hex << currentAddr << std::endl;
        this->playerAddr = 0;
        return;
    }

    this->playerAddr = currentAddr;
    std::cout << "Player Address resolved: " << std::hex << this->playerAddr << std::endl;
    this->netStamina = NetStamina(this->playerAddr);
}

void PlayerObj::setHeath(int newValue)
{
    setValue(OFFSET_HEALTH, newValue);
}

void PlayerObj::setMaxHealth(int newValue)
{
    setValue(OFFSET_MAX_HEALTH, newValue);
}

void PlayerObj::setValue(uintptr_t offset, int newValue)
{
    if (this->playerAddr)
    {
        *(int *)(this->playerAddr + offset) = newValue;
    }
    else
    {
        std::cerr << "Player address is invalid. Cannot set value." << std::endl;
    }
}

template <typename T>
T PlayerObj::getValue(uintptr_t offset)
{
    if (this->playerAddr)
    {
        return *(T *)(this->playerAddr + offset);
    }
    else
    {
        std::cerr << "Player address is invalid. Cannot get value." << std::endl;
        return 0;
    }
}

uintptr_t PlayerObj::getPlayerAddr()
{
    return this->playerAddr;
}

NetStamina PlayerObj::getNetStamina()
{
    return this->netStamina;
}