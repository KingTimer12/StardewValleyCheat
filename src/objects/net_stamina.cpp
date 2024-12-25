#include "net_stamina.hpp"

NetStamina::NetStamina(uintptr_t stackAddr, uintptr_t offsetGameToBaseAddress)
{
    std::vector<Address> pointsOffsets{0x18, 0x110, 0xF70, 0x90, 0x94, 0x18, 0x4D0};
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
    std::cout << "NetStamina Address resolved: " << std::hex << this->objAddr << std::endl;
}