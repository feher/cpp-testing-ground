#pragma once

#include <random>

namespace timed_test
{
    class Test
    {
    public:
        void run(const char * const message);
    private:
        virtual void runImpl(std::default_random_engine &generator) = 0;
    };
}
