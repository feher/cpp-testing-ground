#pragma once

#include <chrono>

namespace highres_clock
{
    struct Clock
    {
        using rep = long long;
        using period = std::nano;
        using duration = std::chrono::duration<rep, period>;
        using time_point =  std::chrono::time_point<highres_clock::Clock>;
        
        static const bool is_steady = true;
    };

    highres_clock::Clock::time_point now();
}
