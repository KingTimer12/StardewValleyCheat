#pragma once

#include "components.hpp"
#include "mm.hpp"

class AbstractObj
{
protected:
    uintptr_t objAddr;

public:
    template <typename T>
    void setValue(uintptr_t offset, T newValue)
    {
        if (this->objAddr)
        {
            *(T *)(this->objAddr + offset) = newValue;
        }
        else
        {
            std::cerr << "Object address is invalid. Cannot set value." << std::endl;
        }
    }

    template <typename T>
    T getValue(uintptr_t offset)
    {
        if (this->objAddr)
        {
            return *(T *)(this->objAddr + offset);
        }
        else
        {
            std::cerr << "Object address is invalid. Cannot get value." << std::endl;
            return 0;
        }
    }
};