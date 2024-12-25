#include "player_obj.hpp"

// Offsets
constexpr uintptr_t OFFSET_HEALTH = 0x6EC;
constexpr uintptr_t OFFSET_MAX_HEALTH = 0x6F0;

PlayerObj::PlayerObj(uintptr_t stackAddr, uintptr_t offsetGameToBaseAddress)
{
    std::vector<Address> pointsOffsets{0x18, 0x110, 0xF70, 0x90, 0x94, 0x18};
    uintptr_t *baseAddress = reinterpret_cast<uintptr_t *>(stackAddr + offsetGameToBaseAddress);
    if (!baseAddress || !(*baseAddress))
    {
        std::cerr << "Failed to read base address" << std::endl;
        this->objAddr = 0;
        return;
    }
    uintptr_t currentAddr = *baseAddress;
    mm::findAddress(&currentAddr, pointsOffsets);
    this->objAddr = currentAddr;
    std::cout << "Player Address resolved: " << std::hex << this->objAddr << std::endl;
}

void PlayerObj::setHeath(int newValue)
{
    setValue(OFFSET_HEALTH, newValue);
}

void PlayerObj::setMaxHealth(int newValue)
{
    setValue(OFFSET_MAX_HEALTH, newValue);
}