#include <vector>
#include <algorithm>

namespace { namespace here {

    template <typename TValue, typename TPredicate>
    static bool AppendToVectorIfAll(std::vector<TValue> &Vector, const TValue &Value, const TPredicate &Predicate)
    {
        const auto EndVectorIt = std::end(Vector);
        const auto ExistingItemIt = std::find_if(std::begin(Vector), EndVectorIt, Predicate);
        if(ExistingItemIt != EndVectorIt)
        {
            return false;
        }
        Vector.push_back(Value);
        return true;
    }

    void Test(int Value)
    {
        auto v = std::vector<int>{};
        AppendToVectorIfAll(v, 5, [=](const int V){ return V != Value; });
    }

}}

namespace lambda
{
    void RunTest()
    {
        here::Test(15);
    }
}

int main()
{
    lambda::RunTest();   
}