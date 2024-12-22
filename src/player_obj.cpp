#include "player_obj.hpp"

// 0x6EC -> Heath
// 0x6F0 -> MaxHealth

PlayerObj::PlayerObj(HANDLE hProcHandle, uint64_t stackAddr, uint64_t offsetGameToBaseAdress)
{
    std::vector<DWORD> pointsOffsets{0x18, 0x110, 0xF70, 0x90, 0x94, 0x18};
    Address ptrWithOffset = stackAddr + offsetGameToBaseAdress;
    std::optional<uint64_t> baseAddrOpt = ReadMemory<uint64_t>(ptrWithOffset);

    if (!baseAddrOpt.has_value())
    {
        std::cerr << "Failed to read memory at initial address: " << std::hex << ptrWithOffset << std::endl;
        return;
    }

    uint64_t baseAddress = baseAddrOpt.value();
    std::cout << "Base Address Read: " << std::hex << baseAddress << std::endl;

    uint64_t currentAddr = baseAddress;

    for (auto offset : pointsOffsets)
    {
        uint64_t tempAddr;
        BOOL result = ReadProcessMemory(hProcHandle, (LPCVOID)(currentAddr + offset), &tempAddr, sizeof(tempAddr), NULL);
        if (!result)
        {
            std::cerr << "Failed to read memory at: " << std::hex << (currentAddr + offset) << std::endl;
            return;
        }
        currentAddr = tempAddr;
    }

    if (currentAddr < 0x1000)
    {
        std::cerr << "Invalid Final Player Address: " << std::hex << currentAddr << std::endl;
        return;
    }

    this->playerAddr = new uint64_t(currentAddr);
    std::cout << "Player Address: " << std::hex << *this->playerAddr << std::endl;
    this->hProcHandle = hProcHandle;
}

void PlayerObj::setValue(uint64_t offset, int newvalue)
{
    if (!this->playerAddr || *this->playerAddr < 0x1000)
    {
        std::cerr << "Invalid Player Address in setValue: " << std::hex
                  << (this->playerAddr ? *this->playerAddr : 0) << std::endl;
        return;
    }
    uint64_t addr = *this->playerAddr + offset;
    if (!WriteProcessMemory(this->hProcHandle, (LPVOID)(addr), &newvalue, sizeof(newvalue), NULL))
    {
        std::cerr << "Failed to write value" << std::endl;
    }
}

void PlayerObj::setHeath(int newvalue)
{
    this->setValue(0x6EC, newvalue);
}

void PlayerObj::setMaxHealth(int newvalue)
{
    this->setValue(0x6F0, newvalue);
}

PlayerObj::~PlayerObj()
{
    if (this->playerAddr)
    {
        delete this->playerAddr;
        this->playerAddr = nullptr;
    }
}