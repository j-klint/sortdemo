#ifndef _WIN32
#include <thread>
#include <chrono>
void inline Sleep(int time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
#endif
