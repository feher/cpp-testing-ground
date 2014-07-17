#pragma once

namespace param_inout {
    // Input
    template <typename T> class oinp;
    template <typename T> oinp<T> oina(const T& arg);
    template <typename T>
    class oinp {
    public:
        oinp(oinp&& other) : m_isDefined{other.m_isDefined}, m_arg{ other.m_arg } { /* empty */ }
        operator const T&() const { return m_arg; }
        const T& arg() const { return m_arg; }
    private:
        oinp(const oinp&) = delete;
        oinp(const T& arg) : m_arg{ arg } { /* empty */ }
        friend inp<T> ina<T>(const T&);
        bool m_isDefined;
        const T& m_arg;
    };
    template <typename T>
    inp<T> ina(const T& arg) { return inp<T>{arg}; }

    // Output
    template <typename T> class outp;
    template <typename T> outp<T> outa(T& arg);
    template <typename T>
    class outp {
    public:
        outp(outp&& other) : m_arg{ other.m_arg } { /* empty */ }
        outp& operator=(const T& otherArg) { m_arg = otherArg; return *this; }
    private:
        outp(const outp&) = delete;
        outp(T& arg) : m_arg{ arg } { /* empty */ }
        friend outp<T> outa<T>(T&);
        bool m_isDefined;
        T& m_arg;
    };
    template <typename T>
    outp<T> outa(T& arg) { return outp<T>{arg}; }

    // Input and output
    template <typename T> class inoutp;
    template <typename T> inoutp<T> inouta(T& arg);
    template <typename T>
    class inoutp {
    public:
        inoutp(inoutp&& other) : m_arg{ other.m_arg } { /* empty */ }
        operator T&() { return m_arg; }
        T& arg() const { return m_arg; }
        inoutp& operator=(const T& otherArg) { m_arg = otherArg; return *this; }
    private:
        inoutp(const inoutp&) = delete;
        inoutp(T& arg) : m_arg{ arg } { /* empty */ }
        friend inoutp<T> inouta<T>(T&);
        bool m_isDefined;
        T& m_arg;
    };
    template <typename T>
    inoutp<T> inouta(T& arg) { return inoutp<T>{arg}; }
}
