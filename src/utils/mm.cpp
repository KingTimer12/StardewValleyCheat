#include "mm.hpp"

void mm::findAddress(uintptr_t *baseAddress, std::vector<Address> pointsOffsets)
{
    uintptr_t currentAddr = *baseAddress;
    for (auto offset : pointsOffsets)
    {
        uintptr_t *nextAddr = reinterpret_cast<uintptr_t *>(currentAddr + offset);
        if (!nextAddr || !(*nextAddr))
        {
            std::cerr << "Failed to resolve pointer chain at offset: " << std::hex << offset << std::endl;
            *baseAddress = 0;
            return;
        }
        currentAddr = *nextAddr;
    }

    if (currentAddr < 0x1000) // Validação para endereços inválidos
    {
        std::cerr << "Invalid Final Address: " << std::hex << currentAddr << std::endl;
        *baseAddress = 0;
        return;
    }

    *baseAddress = currentAddr;
    std::cout << "Address resolved: " << std::hex << *baseAddress << std::endl;
}