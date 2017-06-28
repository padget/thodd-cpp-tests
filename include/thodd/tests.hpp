#ifndef __THODD_TESTS_TESTS_HPP__
#  define  __THODD_TESTS_TESTS_HPP__ 

#  include <tuple>
#  include <type_traits>

#  include <thodd/dsl.hpp>

namespace
thodd
{    
    enum class tests
    {
        given, 
        when, 
        then
    } ;

    extern constexpr auto given = 
        [] (auto&&... __args) 
        { 
            return 
            as_node(
                std::integral_constant<tests, tests::given>{}, 
                [&] () 
                { 
                    return 
                    std::make_tuple(
                        static_cast<decltype(__args)&&>(__args)...) ;
                }) ;
        } ; 

    constexpr auto when =
        [] (auto&& ... __actions) 
        { 
            return
            as_node(
                std::integral_constant<tests, tests::when>{},
                [&] () 
                { 
                    return 
                    std::make_tuple(
                        static_cast<decltype(__actions)&&>(__actions)...) ; 
                }) ;
         } ;

    constexpr auto then = 
        [] (auto&& ... __asserts)
        { 
            return
            as_node(
                std::integral_constant<tests, tests::then>{},
                [&] () 
                { 
                    return 
                    std::make_tuple(
                        static_cast<decltype(__asserts)>(__asserts)...) ; 
                }) ;
        } ;

    template<
        tests id_c, 
        typename act_t>
    using test_node = node<tests, id_c, act_t> ;

    template <typename act_t>
    using given_node = test_node<tests::given, act_t> ;

    template <typename act_t>
    using when_node = test_node<tests::when, act_t> ; 

    template <typename act_t>
    using then_node = test_node<tests::then, act_t> ;

    struct test
    {
        constexpr auto
        interpret(
            given_node<auto> const& __given, 
            when_node<auto> const& __when,
            then_node<auto> const& __then)
        {
            auto&& __args = std::apply(
                    [](auto&&... __acts) { return std::make_tuple(__acts()...) ; },
                     __given.act()) ;
            auto&& __called = __when.act() ;
            auto&& __result = std::apply(__called, __args) ;
            auto&& __test = __then.act() ;
            __test(__result) ;


            return 6 ;
        }
    } ; 
}

#endif