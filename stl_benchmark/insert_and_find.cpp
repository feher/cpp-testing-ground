#include "insert_and_find.hpp"

#include <windows.h> // Needed by HighResClock.
#undef max // Defined in windows.h

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <chrono>

namespace { namespace here
{

    namespace highres_clock
    {
        struct HighResClock
        {
            typedef long long                               rep;
            typedef std::nano                               period;
            typedef std::chrono::duration<rep, period>      duration;
            typedef std::chrono::time_point<HighResClock>   time_point;
            static const bool is_steady = true;

            static time_point now();
        };

        namespace
        {
            const long long g_Frequency = []() -> long long
            {
                LARGE_INTEGER frequency;
                QueryPerformanceFrequency(&frequency);
                return frequency.QuadPart;
            }();
        }

        HighResClock::time_point HighResClock::now()
        {
            LARGE_INTEGER count;
            QueryPerformanceCounter(&count);
            return time_point(duration(count.QuadPart * static_cast<rep>(period::den) / g_Frequency));
        }
    }

    class Test
    {
    public:
        void Run(const char * const Message)
        {
            auto Generator = std::default_random_engine{};
            auto StartTime = highres_clock::HighResClock::now();

            RunImpl(Generator);

            auto EndTime = highres_clock::HighResClock::now();
            std::cout
                << std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()
                << " : " << Message
                << std::endl;
        }
    private:
        virtual void RunImpl(std::default_random_engine &Generator) = 0;
    };

    using Key_t = int;
    using Value_t = int;

    static const auto Iterations = 10000;
    static const auto MaxKey = std::numeric_limits<int>::max();

    static auto Distribution = std::uniform_int_distribution < int > {0, MaxKey};

    class Vector_Test : public Test
    {
        virtual void RunImpl(std::default_random_engine &Generator) override
        {
            using KeyVal_t = std::pair < Key_t, Value_t > ;
            auto Container = std::vector < KeyVal_t > {};
            Container.reserve(50);
            for(auto i = 0; i < Iterations; ++i)
            {
                auto Value = Value_t{13};
                auto Key = Key_t{Distribution(Generator)};
                auto KeyValue = std::make_pair(Key, Value);
                const auto It = std::find_if(std::begin(Container), std::end(Container), [=](const KeyVal_t &KeyValue){ return KeyValue.first == Key; });
                if(It == std::end(Container))
                {
                    Container.push_back(KeyValue);
                }
            }
        }
    };

    class Map_Test : public Test
    {
        virtual void RunImpl(std::default_random_engine &Generator) override
        {
            auto Container = std::map<Key_t, Value_t>{};
            for(auto i = 0; i < Iterations; ++i)
            {
                auto Value = Value_t{13};
                auto Key = Key_t{Distribution(Generator)};
                auto KeyValue = std::make_pair(Key, Value);
                const auto It = Container.find(Key);
                if(It == std::end(Container))
                {
                    Container[Key] = Value;
                }
            }
        }
    };

    class Set_KeyOnly_Test : public Test
    {
        virtual void RunImpl(std::default_random_engine &Generator) override
        {
            auto Container = std::set < Key_t > {};
            for(auto i = 0; i < Iterations; ++i)
            {
                auto Value = Value_t{13};
                auto Key = Key_t{Distribution(Generator)};
                auto KeyValue = std::make_pair(Key, Value);
                Container.insert(Key);
            }
        }
    };

    class UnorderedMap_Test : public Test
    {
        virtual void RunImpl(std::default_random_engine &Generator) override
        {
            auto Container = std::unordered_map < Key_t, Value_t > {};
            for(auto i = 0; i < Iterations; ++i)
            {
                auto Value = Value_t{13};
                auto Key = Key_t{Distribution(Generator)};
                auto KeyValue = std::make_pair(Key, Value);
                const auto It = Container.find(Key);
                if(It == std::end(Container))
                {
                    Container[Key] = Value;
                }
            }
        }
    };

    class UnorderedSet_KeyOnly_Test : public Test
    {
        virtual void RunImpl(std::default_random_engine &Generator) override
        {
            auto Container = std::unordered_set < Key_t > {};
            for(auto i = 0; i < Iterations; ++i)
            {
                auto Value = Value_t{13};
                auto Key = Key_t{Distribution(Generator)};
                auto KeyValue = std::make_pair(Key, Value);
                Container.insert(Key);
            }
        }
    };
}}

namespace insert_and_find
{
    void RunTest()
    {
        for(auto i = 0; i < 5; ++i)
        {
            here::Vector_Test{}.Run("Vector_Test");
            here::Map_Test{}.Run("Map_Test");
            here::Set_KeyOnly_Test{}.Run("Set_KeyOnly_Test");
            here::UnorderedMap_Test{}.Run("UnorderedMap_Test");
            here::UnorderedSet_KeyOnly_Test{}.Run("UnorderedSet_KeyOnly_Test");
        }

        {
            auto v = std::vector < int > {};
            std::cout << "Empty vector capacity = " << v.capacity() << std::endl;
            for(auto i = 0; i < 50; ++i)
            {
                v.push_back(3);
                std::cout << "Vector capacity = " << v.capacity() << std::endl;
            }
        }

        {
            auto v = std::vector < int > {};
            v.reserve(50);
            std::cout << "Capacity of empty vector with 50 reserved items = " << v.capacity() << std::endl;
            v.push_back(3);
            std::cout << "Vector capacity with 1 element = " << v.capacity() << std::endl;
        }
    }
}
