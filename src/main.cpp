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

int divide(int a, int b)
{
    return a / b ;
}

int mult(int a, int b)
{
    return a * b ;
}



int main (int i, char* c[])
try 
{
    using namespace thodd ;
    
    auto test_calc = 
        $test << given(val(1), val(2), val(10), val(5)) 
              << when(
                    bind(&::add,    $0, $1), 
                    bind(&::minus,  $0, $1), 
                    bind(&::divide, $2, $3),
                    bind(&::mult,   $2, $2)) 
              << then(
                    $0 == val(3), 
                    $1 == val(-1), 
                    $2 == val(2), 
                    $3 == val(100)) ;

    std::cout << std::boolalpha << test_calc() << std::endl ;

    //or 

   auto test_add = 
        $test << given(val(1), val(2)) 
              << when(bind(&::add, $0, $1)) 
              << then($0 == val(3)) ;
    auto test_minus = 
        $test << given(val(1), val(2)) 
              << when(bind(&::minus, $0, $1)) 
              << then($0 == val(-1)) ;
    auto test_mult = 
        $test << given(val(5)) 
              << when(bind(&::mult, $0, $0)) 
              << then($0 == val(25)) ;
    auto test_divide = 
        $test << given(val(10), val(5)) 
              << when(bind(&::divide, $0, $1)) 
              << then($0 == val(2)) ;

    std::cout << std::boolalpha << test_add()    << '\n' ;
    std::cout << std::boolalpha << test_minus()  << '\n' ;
    std::cout << std::boolalpha << test_mult()   << '\n' ;
    std::cout << std::boolalpha << test_divide() << '\n' ;
    std::cout << std::endl ;
    
    return 0;
}
catch(std::exception & e)
{
    std::cout << e.what() << std::endl;
}