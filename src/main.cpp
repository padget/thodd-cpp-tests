#include <iostream>
#include <exception>
#include <fstream>

#include <thodd/tests.hpp>

int add(int a, int b)
{
    return a + b ;
}

int main (int i, char* c[])
try 
{
    using namespace thodd ;
    
    go<test>{}(
        given(
            [] { return 1 ; }, 
            [] { return 2 ; }) > 
        when([] (auto const& a, auto const& b) { std::cout << a << ' ' << b << std::endl;return add(a, b); }) > 
        then([] (auto const& r) { std::cout << r << std::endl; return r == 3 ; })) ;
    
    
    std::cout << "coucou" << std::endl; 


    return 0;
}
catch(std::exception & e)
{
    std::cout << e.what() << std::endl;
}