#include "boost_format_test.hpp"
#include "highres_clock.hpp"

#include "boost/format.hpp"

#include <string>
#include <iostream>
#include <random>
#include <array>
#include <cassert>
#include <fstream>
#include <io.h>
#include <memory>
#include <unordered_map>

namespace { namespace here {

static const auto resultFilePath = "c:/temp/boost_format_test_output_candeletethis.txt";
static const auto iterations = 500;
static const auto maxInt = std::numeric_limits<int>::max();
static const auto maxDouble = double{5000000.0};

void printWithPrintf(int intNum1, int intNum2, double doubleNum1, double doubleNum2, const char * const text1, const char * const text2)
{
    printf("%d %g %s %d %g %s\n", intNum1, doubleNum1, text1, intNum2, doubleNum2, text2);
}

void printWithBoostAndPrintf(int intNum1, int intNum2, double doubleNum1, double doubleNum2, const char * const text1, const char * const text2)
{
    const auto m = boost::format("%1% %2% %3% %4% %5% %6%") % intNum1 % doubleNum1 % text1 % intNum2 % doubleNum2 % text2;
    printf("%s\n", boost::str(m).c_str());
}

void printWithBoostAndFlushedPrintf(int intNum1, int intNum2, double doubleNum1, double doubleNum2, const char * const text1, const char * const text2)
{
    const auto m = boost::format("%1% %2% %3% %4% %5% %6%") % intNum1 % doubleNum1 % text1 % intNum2 % doubleNum2 % text2;
    printf("%s\n", boost::str(m).c_str());
    fflush(stdout);
}

void printWithBoostAndStreams(int intNum1, int intNum2, double doubleNum1, double doubleNum2, const char * const text1, const char * const text2)
{
    std::cout << boost::format("%1% %2% %3% %4% %5% %6%") % intNum1 % doubleNum1 % text1 % intNum2 % doubleNum2 % text2 << '\n';
}

void printWithBoostAndWrite(int intNum1, int intNum2, double doubleNum1, double doubleNum2, const char * const text1, const char * const text2)
{
    const auto m = boost::format("%1% %2% %3% %4% %5% %6%") % intNum1 % doubleNum1 % text1 % intNum2 % doubleNum2 % text2;
    const auto &mstr = boost::str(m);
    ::_write(1, mstr.c_str(), static_cast<unsigned int>(mstr.size()));
}

void printWithStreams(int intNum1, int intNum2, double doubleNum1, double doubleNum2, const char * const text1, const char * const text2)
{
    std::cout << intNum1 << ' ' << doubleNum1 << ' ' << text1 << ' '
              << intNum1 << ' ' << doubleNum2 << ' ' << text2 << '\n';
}

using PrintFunc_t = void (*)(int, int, double, double, const char * const, const char * const);

class Test
{
public:
    Test();
    void runAllTests();
    void runOneTest(const std::string &testSubCase);

private:
    void generateTestData();

    void runTest(const std::string &message, const here::PrintFunc_t printFunc);

    std::default_random_engine m_generator {};

    std::uniform_int_distribution<int> m_intDistribution {0, here::maxInt};
    std::uniform_real_distribution<double> m_doubleDistribution {0, here::maxDouble};

    const std::string m_messageString1;
    const std::string m_messageString2;

    std::array<int, here::iterations> m_intData1;
    std::array<int, here::iterations> m_intData2;
    std::array<double, here::iterations> m_doubleData1;
    std::array<double, here::iterations> m_doubleData2;
    std::array<std::string, here::iterations> m_textData1;
    std::array<std::string, here::iterations> m_textData2;

    std::unordered_map<std::string, here::PrintFunc_t> m_testSubCases;
};

Test::Test()
    : m_messageString1("This is a TEST message?"),
      m_messageString2("TEST The apple was green now it's TEST.")
{
    m_testSubCases = std::unordered_map<std::string, here::PrintFunc_t>{
        { "boost_printf", here::printWithBoostAndPrintf },
        { "boost_flushed_printf", here::printWithBoostAndFlushedPrintf },
        { "boost_write", here::printWithBoostAndWrite },
        { "boost_stream", here::printWithBoostAndStreams },
        { "stream", here::printWithStreams },
        { "printf", here::printWithPrintf },
    };
    generateTestData();
}

void Test::generateTestData()
{
    for(auto i = 0; i < here::iterations; ++i)
    {
        const auto num1 = m_intDistribution(m_generator);
        const auto num2 = m_intDistribution(m_generator);
        const auto num3 = m_doubleDistribution(m_generator);
        const auto num4 = m_doubleDistribution(m_generator);
        const auto &num1AsString = std::to_string(num1);
        const auto &num3AsString = std::to_string(num3);

        const auto pattern = std::string{"TEST"};

        auto text1 = m_messageString1;
        auto patternPos = text1.find(pattern);
        assert(patternPos != std::string::npos);
        text1.replace(patternPos, pattern.size(), num1AsString);

        auto text2 = m_messageString2;
        patternPos = text2.find(pattern);
        assert(patternPos != std::string::npos);
        text2.replace(patternPos, pattern.size(), num1AsString);
        patternPos = text2.find(pattern);
        assert(patternPos != std::string::npos);
        text2.replace(patternPos, pattern.size(), num3AsString);

        m_intData1[i] = num1;
        m_intData2[i] = num2;
        m_doubleData1[i] = num3;
        m_doubleData2[i] = num4;
        m_textData1[i] = text1;
        m_textData2[i] = text2;
    }
}

void Test::runAllTests()
{
    for (const auto &testSubCase : m_testSubCases)
    {
        runTest(testSubCase.first, testSubCase.second);
    }
}

void Test::runOneTest(const std::string &testSubCase)
{
    runTest(testSubCase, m_testSubCases[testSubCase]);
}

void Test::runTest(const std::string &message, const here::PrintFunc_t printFunction)
{
    auto StartTime = highres_clock::now();

    for(auto i = 0; i < here::iterations; ++i)
    {
        printFunction(m_intData1[i], m_intData2[i],
                      m_doubleData1[i], m_doubleData2[i],
                      m_textData1[i].c_str(), m_textData2[i].c_str());
    }
     
    auto EndTime = highres_clock::now();

    std::ofstream file {here::resultFilePath, std::ios::app};
    file
        << std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count()
        << " ns : " << message
        << std::endl;
}

}}

void boost_format_test::test(const std::string &testSubCase)
{
    auto test = std::make_unique<here::Test>();
    if(testSubCase == "all")
    {
        test->runAllTests();
    }
    else
    {
        test->runOneTest(testSubCase);
    }
}
