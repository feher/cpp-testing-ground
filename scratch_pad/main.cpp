#include "header1.hpp"
#include <iostream>
#include <string>
#include <algorithm>

template<typename T>
struct TD;

void Gigi(const std::string &String)
{
    std::cout << "const&: " << String << "\n";
}

void Gigi(std::string &&String)
{
    std::cout << "&&: " << String << "\n";
}

template<typename T>
void Fifi(T&& Arg)
{
    Gigi(std::forward<T>(Arg));
}

bool IsOverlap1(int PositionASeriesNumber, int PositionBSeriesNumber, int PositionASeriesStartNumber, int PositionBSeriesStartNumber)
{
    return PositionBSeriesStartNumber <= PositionASeriesNumber
           && PositionASeriesStartNumber <= PositionBSeriesNumber;
}

bool IsOverlap2(int PositionASeriesNumber, int PositionBSeriesNumber, int PositionASeriesStartNumber, int PositionBSeriesStartNumber)
{
    const auto MaxSeriesNumber = std::max(PositionASeriesNumber, PositionBSeriesNumber);
    const auto MaxStartNumber = std::max(PositionASeriesStartNumber, PositionBSeriesStartNumber);
    const auto IsOverlap =
        (MaxStartNumber <= PositionASeriesNumber) &&
        (MaxStartNumber <= PositionBSeriesNumber);
    return IsOverlap;
}

int main(int argc, char **argv)
{
    int a, b, c, d;
    a = argc;
    b = a * 4;
    c = b * 5;
    d = c * 10;
    auto r1 = IsOverlap1(a,b,c,d);
    auto r2 = IsOverlap2(a, b, c, d);
    return r1 + r2;
}
