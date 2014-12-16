#include "highres_clock.hpp"

#include <windows.h>
#undef max
#undef min

#include <chrono>

namespace {
    namespace here
    {
        // Performance-counter frequency, in counts per second.
        const auto g_Frequency = []()
            {
                LARGE_INTEGER frequency;
                QueryPerformanceFrequency(&frequency);
                return frequency.QuadPart;
            }();
    }
}


highres_clock::Clock::time_point highres_clock::now()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    const auto ticksPerSecond = static_cast<highres_clock::Clock::rep>(highres_clock::Clock::period::den);
    const auto numberOfTicks = count.QuadPart * ticksPerSecond / here::g_Frequency;
    return highres_clock::Clock::time_point( highres_clock::Clock::duration(numberOfTicks) );
}
