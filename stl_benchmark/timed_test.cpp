#include "timed_test.hpp"
#include "highres_clock.hpp"

#include <iostream>

namespace timed_test
{
    void Test::run(const char * const message)
    {
        auto generator = std::default_random_engine{};
        auto startTime = highres_clock::now();

        runImpl(generator);

        auto endTime = highres_clock::now();
        std::cout
            << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count()
            << " : " << message
            << std::endl;
    }
}
