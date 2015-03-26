#include "indexed_vector.hpp"

#include <iostream>
#include <string>

struct MyType
{
    double field1;
    int field2;
    std::string field3;
};

struct SortByField1
{
    bool IsLess(const MyType &a, const MyType &b)
    {
        return a.field1 < b.field1;
    }
};

struct SortByField1AndField3
{
    bool IsLess(const MyType &a, const MyType &b)
    {
        if (a.field1 < b.field1)
        {
            return true;
        }
        if (a.field1 > b.field1)
        {
            return false;
        }
        return a.field3 < b.field3;
    }
};

int main()
{
    auto iv =
        feher::IndexedVector<
            MyType,
            SortByField1,
            SortByField1AndField3>{};
    iv.addItem(MyType{ 6.0, 3, "hello" });
    iv.addItem(MyType{ 2.0, 45, "apple" });
    iv.addItem(MyType{ 5.0, 2, "lion" });
    iv.addItem(MyType{ 3.0, 30, "queen" });
    iv.addItem(MyType{ 3.0, 30, "pear" });

    for (auto i = feher::IndexedVectorPosition{ 0 }; i < iv.size(); ++i)
    {
        std::cout << iv.itemAt<SortByField1>(i).field1 << std::endl;
        std::cout << iv.itemAt<SortByField1AndField3>(i).field1 << " "
                  << iv.itemAt<SortByField1AndField3>(i).field3 << std::endl;
    }

    return 0;
}
