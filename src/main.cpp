#include <iostream>
#include <exception>
#include <fstream>

#include <thodd/tests.hpp>
#include <thodd/functional.hpp>

auto add(auto a, auto b)
{
    return a + b ;
}

auto minus(auto a, auto b)
{
    return a - b ;
}

auto div(auto a, auto b)
{
    return a / b ;
}

int main (int i, char* c[])
try 
{
    using namespace thodd ;
    
    std::cout << std::boolalpha << 
        go<test>{}(
            given(val(1), val(2), nothing()) > 
            when(bind(&::add, $0, $1), 
                 bind(&::minus, $2, $1)) > 
            then($0 == val(3), 
                 $1 == val(1))) << std::endl ;

    return 0;
}
catch(std::exception & e)
{
    std::cout << e.what() << std::endl;
}