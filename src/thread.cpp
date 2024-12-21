#include "thread.hpp"

uint64_t GetThreadStartAddress(HANDLE processHandle, HANDLE hThread)
{
    /* rewritten from https://github.com/cheat-engine/cheat-engine/blob/master/Cheat%20Engine/CEFuncProc.pas#L3080 */
    uint64_t used = 0, ret = 0;
    uint64_t stacktop = 0, result = 0;

    MODULEINFO mi;

    GetModuleInformation(processHandle, GetModuleHandleW(L"kernel32.dll"), &mi, sizeof(mi));
    stacktop = (uint64_t)GetThreadStackTopAddress_x86(processHandle, hThread);

    CloseHandle(hThread);

    if (stacktop)
    {
        // find the stack entry pointing to the function that calls "ExitXXXXXThread"
        // Fun thing to note: It's the first entry that points to a address in kernel32

        uint64_t *buf64 = new uint64_t[8192];

        if (ReadProcessMemory(processHandle, (LPCVOID)(stacktop - 8192), buf64, 8192, NULL))
        {
            for (int i = 8192 / 8 - 1; i >= 0; --i)
            {
                if (buf64[i] >= (uint64_t)mi.lpBaseOfDll && buf64[i] <= (uint64_t)mi.lpBaseOfDll + mi.SizeOfImage)
                {
                    result = stacktop - 8192 + i * 8;
                    break;
                }
            }
        }

        delete buf64;
    }

    return result;
}

uint64_t GetThreadStack(uint8_t maxStackNum, HANDLE hProcHandle, Pid *pid)
{
    std::vector<Thread> threads = EnumThreads().value();
    uint8_t stackNum = 0;
    for (Thread thread : threads)
    {
        HANDLE threadHandle = OpenThread(THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, thread.tid);
        uint64_t threadStartAddress = GetThreadStartAddress(hProcHandle, threadHandle);
        std::cout << "TID:" << to_string(thread.tid) << " = THREADSTACK" << to_string(stackNum) << " BASE ADDRESS: " << to_string(threadStartAddress) << std::endl;
        if (stackNum == maxStackNum)
        {
            return threadStartAddress;
        }
        stackNum++;
    }

    return 0;
}