#include "insert_and_find.hpp"
#include "timed_test.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <algorithm>

namespace { namespace here
{
    using Key_t = int;
    using Value_t = int;

    static const auto Iterations = 10000;
    static const auto MaxKey = std::numeric_limits<int>::max();

    static auto Distribution = std::uniform_int_distribution < int > {0, MaxKey};

    class Vector_Test : public timed_test::Test
    {
        virtual void runImpl(std::default_random_engine &Generator) override
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

    class Map_Test : public timed_test::Test
    {
        virtual void runImpl(std::default_random_engine &Generator) override
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

    class Set_KeyOnly_Test : public timed_test::Test
    {
        virtual void runImpl(std::default_random_engine &Generator) override
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

    class UnorderedMap_Test : public timed_test::Test
    {
        virtual void runImpl(std::default_random_engine &Generator) override
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

    class UnorderedSet_KeyOnly_Test : public timed_test::Test
    {
        virtual void runImpl(std::default_random_engine &Generator) override
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

void insert_and_find::runTest()
{
    for(auto i = 0; i < 5; ++i)
    {
        here::Vector_Test{}.run("Vector_Test");
        here::Map_Test{}.run("Map_Test");
        here::Set_KeyOnly_Test{}.run("Set_KeyOnly_Test");
        here::UnorderedMap_Test{}.run("UnorderedMap_Test");
        here::UnorderedSet_KeyOnly_Test{}.run("UnorderedSet_KeyOnly_Test");
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
