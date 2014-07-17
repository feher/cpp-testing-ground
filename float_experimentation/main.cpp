#include <iostream>
#include <cstdint> // uint32_t

// 32 bit float
struct Float
{
    explicit Float(float pf) : f{pf} {}
    union {
        uint32_t i; // integer representation
        float f; // float representation
        // Little-Endian representation of parts
        struct {
            uint32_t m : 23; // mantissa
            uint32_t e : 8;  // exponent
            uint32_t s : 1; // sign bit
        } le_part;
        // Big-Endian representation of parts
        struct {
            uint32_t s : 1;  // sign bit
            uint32_t e : 8;  // exponent
            uint32_t m : 23; // mantissa
        } be_part;
    };
};

// 64 bit double
struct Double
{
    explicit Double(double pd) : d{pd} {}
    union {
        uint64_t i; // integer representation
        double d; // double representation
        // Little-Endian representation of parts
        struct {
            uint64_t m : 52; // mantissa
            uint64_t e : 11;  // exponent
            uint64_t s : 1; // sign bit
        } le_part;
        // Big-Endian representation of parts
        struct {
            uint64_t s : 1;  // sign bit
            uint64_t e : 11;  // exponent
            uint64_t m : 52; // mantissa
        } be_part;
    };
};

int main()
{
    auto af = Float{0.0f};
    auto bf = Float{0.0f};
    auto ad = Double{0.0};
    auto bd = Double{0.0};
    return 0;
}