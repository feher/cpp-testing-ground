#define _UNICODE
#define UNICODE
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <tchar.h>
using namespace std;

void Test(const char * CodePage)
{
    cout << "Requested locale: " << CodePage << endl;
    //    setlocale(LC_ALL, "en-US");
    cout << "Selected locale: " << setlocale(LC_ALL, CodePage) << endl;
    auto us_b = 'b';
    auto hun_aa2 = static_cast<signed char>(0xe1); // Unicode code point
    auto hun_aa3 = static_cast<signed char>(160); // ANSI code page index
    auto us_B = toupper(us_b);
    auto hun_AA2 = toupper(hun_aa2);
    auto hun_AA3 = toupper(hun_aa3);
    auto us_cB = static_cast<char>(toupper(us_b));
    auto hun_cAA2 = static_cast<char>(toupper(hun_aa2));
    auto hun_cAA3 = static_cast<char>(toupper(hun_aa3));

    cout << "  us b: " << us_b << us_cB << endl;
    cout << "  hun aa unicode: " << hun_aa2 << hun_cAA2 << endl;
    cout << "  hun aa ansi: " << hun_cAA3 << endl;

    auto fname = string{R"(C:\Users\Gabor\Data\Level2\Temporary\)"} +string{hun_aa3} +string{CodePage};
    auto of = ofstream{fname};
    of << hun_aa3;
    of.close();
}

int main()
{
    Test(".437");
    Test(".852");
    Test("en-US");
    _tcslen(L"hello");
    auto apple = std::string{"\x6c\x49\x8b\xed"};
    return 0;
}
