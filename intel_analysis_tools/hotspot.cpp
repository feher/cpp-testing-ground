#include <array>
#include <random>
#include <algorithm>

namespace { namespace here {

using Engine_t = std::mt19937;

double GenerateRandomNumber(here::Engine_t &Generator)
{
    auto Distribution = std::uniform_real<double>{1, 5000};
    return Distribution(Generator);
}

class Test_c
{
public:
    Test_c();
    void Run();
private:
    void HotFunction();
    here::Engine_t m_Generator;
};

Test_c::Test_c()
{
    m_Generator.seed(328793872193209);
}

void Test_c::HotFunction()
{
    auto d = std::array<double, 4000>{};
    std::generate(std::begin(d), std::end(d), [this](){
        return here::GenerateRandomNumber(m_Generator);
    });
}

void Test_c::Run()
{
    HotFunction();
}

} } // namespace

void Hotspot()
{
    auto Test = here::Test_c{};
    Test.Run();
}
