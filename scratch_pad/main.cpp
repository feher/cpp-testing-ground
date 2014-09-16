//#include <string>
//#include <iostream>
//#include <functional>
//#include <utility>
//#include <tuple>
//#include <type_traits>
//#include <vector>
//
//// const is part of the contract --> programmer defined
//// &, && are optimizations --> compiler defined/deduced
//
//// For function signatures:
//// --------------------------
//void g(A @a)
//{
//    // sizeof(A) > sizeof(void*) || A::A(const A&): A# --> A&
//    // else: A# --> A
//}
//// For forward declarations, it cannot be done always:
////
//// f.hpp:
//void g(A @); // <-- @ cannot be deduced without seeing the definition of A!
//
//// For local variables:
//// --------------------------
//void f(A &a)
//{
//    auto @B = DoSomething();
//}
//
//int main()
//{
//    return 0;
//}

//struct A
//{
//    double arr[50];
//};
//
//A g()
//{
//    A a;
//    a.arr[40] = 5.5;
//    return a;
//}
//
//A f()
//{
//    return g();
//}
//
//A h()
//{
//    return f();
//}
//
//int main()
//{
//    A a;
//    a = h();
//    a.arr[40] = a.arr[45];
//    return static_cast<int>(a.arr[40]);
//}

#include <iostream>
#include <fstream>
#include <string>

std::string GetTableName(const std::string &Line)
{
    const auto TablePos = Line.find("Table ");
    if(TablePos == std::string::npos)
    {
        return "";
    }
    const auto NameStartPos = TablePos + 6;
    const auto NameEndPos = Line.find(' ', NameStartPos);
    return Line.substr(NameStartPos, NameEndPos - NameStartPos);
}

std::string DumpTableToFile(std::ifstream &InStream, const std::string &TableName)
{
    std::cout << "Dumping " << TableName << std::endl;

    const auto OutFile = std::string{"C:/Temp/scratchpad_dump/scratchpad.dump."} + TableName;
    auto OutStream = std::ofstream{OutFile, std::ios::app};
    if(!OutStream.is_open())
    {
        std::cout << "Cannot open output file:" << OutFile << std::endl;
        return false;
    }

    OutStream << "Table: " << TableName << "\n";

    auto IsTableFound = false;
    auto Line = std::string{};
    do {
        std::getline(InStream, Line);
        if(Line.find("Table ") != std::string::npos)
        {
            IsTableFound = true;
        }
        else
        {
            OutStream << Line << "\n";
        }
    } while(InStream.good() && !IsTableFound);

    return Line;
}

int main()
{
    const auto InFile = std::string{"C:/Models/TestModel/model.dmp"};
    auto InStream = std::ifstream{InFile};
    if(!InStream.is_open())
    {
        std::cout << "Cannot open file" << std::endl;
        return 0;
    }
    auto Line = std::string{};

    auto IsTableFound = false;
    std::getline(InStream, Line);
    do {
        const auto &TableName = GetTableName(Line);
        if(!TableName.empty())
        {
            Line = DumpTableToFile(InStream, TableName);
        }
        else
        {
            std::getline(InStream, Line);
        }
    } while(InStream.good());

    return 0;
}

//#include <memory>
//#include <iostream>
//void MyFree(void *p)
//{
//    free(p);
//    std::cout << "MyFree()" << std::endl;
//}
//int main()
//{
//    std::unique_ptr<void, decltype(MyFree)*> m{(void*)malloc(1000), MyFree};
//    return 0;
//}
