#include "highres_clock.hpp"

#include <windows.h>
#undef max
#undef min

#include <chrono>

namespace { namespace here
{
    const long long g_Frequency = []() -> long long
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency.QuadPart;
    }();
}}


highres_clock::Clock::time_point highres_clock::now()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    const auto rep = static_cast<highres_clock::Clock::rep>(highres_clock::Clock::period::den);
    return highres_clock::Clock::time_point(
            highres_clock::Clock::duration(
                count.QuadPart * rep / here::g_Frequency));
}
