#include "boost_format_test.hpp"

#include <string>
#include <iostream>

int main(int argc, const char ** argv)
{
    if(argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " test-case test-subcase\n";
        std::cout << "  Test cases:";
        std::cout << "    boost_format\n";
        std::cout << "    Subcases:\n";
        std::cout << "      boost_printf         : Boost\n";
        std::cout << "      boost_flushed_printf\n";
        std::cout << "      boost_write\n";
        std::cout << "      boost_stream\n";
        std::cout << "      stream\n";
        std::cout << "      printf\n";
    }
    const auto testCase = std::string{argv[1]};
    if (testCase == "boost_format")
    {
        boost_format_test::test(argv[2]);
    }
    return 0;
}
