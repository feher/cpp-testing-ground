#pragma once

#include <chrono>

namespace highres_clock
{
    struct Clock
    {
        using rep = long long;    // Type of "number of ticks".
        using period = std::nano; // Number of seconds from one tick to the next.
        using duration = std::chrono::duration<rep, period>;
        using time_point =  std::chrono::time_point<highres_clock::Clock>;
        
        static const bool is_steady = true;
    };

    highres_clock::Clock::time_point now();
}
