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


#include <memory>

int main()
{
    auto Data =
        std::unique_ptr<double, void(*)(void*)>{
            reinterpret_cast<double*>(malloc(sizeof(double) * 50)),
            free };
    return 0;
}


//#include <memory>
//#include <iostream>
//
//void MyFree(void *p)
//{
//    free(p);
//    std::cout << "MyFree()" << std::endl;
//}
//
//template <typename T>
//struct TypeDisplayer;
//int main()
//{
//    // TypeDisplayer<decltype(MyFree)*> MyFreeType;
//    // main.cpp(77): error C2079: 'MyFreeType' uses undefined struct 'TypeDisplayer<void (__cdecl *)(void *)>'
//
//    auto m1 = std::unique_ptr<void, decltype(MyFree)*>{ malloc(1000), MyFree };
//    auto m2 = std::unique_ptr<void, decltype(free)*>{ malloc(1000), free };
//    return 0;
//}
