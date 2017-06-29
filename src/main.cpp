#include <iostream>
#include <exception>
#include <fstream>

#include <thodd/tests.hpp>
#include <thodd/functional.hpp>

int add(int a, int b)
{
    return a + b ;
}

int minus(int a, int b)
{
    return a - b ;
}

int main (int i, char* c[])
try 
{
    using namespace thodd ;
    
    std::cout << std::boolalpha << 
        go<test>{}(
            given(
                [] { return 1 ; }, 
                [] { return 2 ; }) > 
            when(
                bind(&::add, $0, $1), 
                bind(&::minus, $2, $1), 
                $3 ++ ) > 
            then(
                $0 == val(3),
                $1 == val(1), 
                $2 == val(2))) << std::endl ;

    return 0;
}
catch(std::exception & e)
{
    std::cout << e.what() << std::endl;
}