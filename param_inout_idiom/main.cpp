#include "param_inout.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace param_inout;
using namespace std;
#define PRINT(arg) cout << __FUNCTION__ << ":" << __LINE__ << ": "<< arg << " " << endl

double func1(inp<int> p) {
    // p = 1; // Error: p is read-only.
    return p * 2.2;
}

void func2(outp<int> p) {
    // int a = p; // Error: p is write-only.
    p = 88;
}

void func3(inoutp<string> p) {
    auto t = string(p); // p is readable.
    p = "Hello ";       // p is writable.
    p = string(p) + t;  // p is readable and writable.
}

void func4(inp<string> pattern,
           inp<vector<string>> items,
           inoutp<string> message,
           outp<int> matchCount) {
    PRINT(message.arg());
    auto& ritems = items.arg();
    matchCount = count_if(begin(ritems), end(ritems),
        [&](const string& a) { return a.find(pattern) != string::npos; });
    message = "Done";
}

void func5(inp<int> p1, outp<int> p2, inoutp<string> p3) {
    // func1(p1); // Error! Good! inp::inp(const inp&) is private.
    func1(ina(p1));
    func2(outa(p2));
    func3(inouta(p3));
}

int main() {
    // auto a = func1(ina(2.2)); // Error: Cannot convert ina<double> to ina<int>
    // auto a = func1(2); // Error: inp::inp(const int&) is private.
    auto a0 = func1(ina(static_cast<int>(2.2)));   PRINT(a0);
    auto a1 = func1(ina(2));                       PRINT(a1);
    auto a2 = 0;                func2(outa(a2));   PRINT(a2);
    auto a3 = string{"world!"}; func3(inouta(a3)); PRINT(a3);

    auto a4 = vector<string>{"avocado", "apple", "plum", "apricot", "orange"};
    auto a5 = string{"Searching..."};
    auto a6 = 0;
    func4(ina(string{ "ap" }), ina(a4), inouta(a5), outa(a6));
    PRINT(a5);  PRINT(a6);

    func5(ina(5), outa(a6), inouta(a5));  PRINT(a5); PRINT(a6);

    return 0;
}
