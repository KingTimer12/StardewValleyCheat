#pragma once

#include <ntinfo.hpp>
#include "components.hpp"

uint64_t GetThreadStartAddress(HANDLE processHandle, HANDLE hThread);
uint64_t GetThreadStack(uint8_t maxStackNum, HANDLE hProcHandle, Pid *pid);