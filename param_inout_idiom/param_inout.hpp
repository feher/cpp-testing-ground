#pragma once
namespace param_inout {
    // Input
    template <typename T> class inp;
    template <typename T> inp<T> ina(const T&);
    template <typename T> inp<T> ina(const inp<T>&);
    template <typename T>
    class inp {
    public:
        inp(inp&& other) : m_arg{other.m_arg} { /* empty */ }
        operator const T&() const { return m_arg; }
        const T& arg() const { return m_arg; }
    private:
        inp(const inp&) = delete;
        inp(const T& arg) : m_arg{arg} { /* empty */ }
        friend inp<T> ina<T>(const T&);
        friend inp<T> ina<T>(const inp<T>& arg);
        const T& m_arg;
    };
    template <typename T>
    inp<T> ina(const T& arg) { return inp<T>{arg}; }
    template <typename T>
    inp<T> ina(const inp<T>& param) { return inp<T>{param.m_arg}; }

    // Output
    template <typename T> class outp;
    template <typename T> outp<T> outa(T&);
    template <typename T> outp<T> outa(outp<T>&);
    template <typename T>
    class outp {
    public:
        outp(outp&& other) : m_arg{other.m_arg} { /* empty */ }
        outp& operator=(const T& otherArg) { m_arg = otherArg; return *this; }
    private:
        outp(const outp&) = delete;
        outp(T& arg) : m_arg{arg} { /* empty */ }
        friend outp<T> outa<T>(T&);
        friend outp<T> outa<T>(outp<T>&);
        T& m_arg;
    };
    template <typename T>
    outp<T> outa(T& arg) { return outp<T>{arg}; }
    template <typename T>
    outp<T> outa(outp<T>& param) { return outp<T>{param.m_arg}; }

    // Input and output
    template <typename T> class inoutp;
    template <typename T> inoutp<T> inouta(T&);
    template <typename T> inoutp<T> inouta(inoutp<T>&);
    template <typename T>
    class inoutp {
    public:
        inoutp(inoutp&& other) : m_arg{other.m_arg} { /* empty */ }
        operator T&() { return m_arg; }
        T& arg() const { return m_arg; }
        inoutp& operator=(const T& otherArg) { m_arg = otherArg; return *this; }
    private:
        inoutp(const inoutp&) = delete;
        inoutp(T& arg) : m_arg{arg} { /* empty */ }
        friend inoutp<T> inouta<T>(T&);
        friend inoutp<T> inouta<T>(inoutp<T>&);
        T& m_arg;
    };
    template <typename T>
    inoutp<T> inouta(T& arg) { return inoutp<T>{arg}; }
    template <typename T>
    inoutp<T> inouta(inoutp<T>& param) { return inoutp<T>{param.m_arg}; }
}
