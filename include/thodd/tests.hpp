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


    template<
        size_t idx>
    constexpr auto
    ___call (
        auto&& __calls, 
        auto&& __args) 
    {
        if constexpr (idx < std::tuple_size_v<std::decay_t<decltype(__calls)>>)
        {
            auto&& __call = std::get<idx>(static_cast<decltype(__calls)&&>(__calls)) ; 
            using res_t = decltype(std::apply(__call, static_cast<decltype(__args)&&>(__args))) ;

            if constexpr (std::is_void_v<std::decay_t<res_t>>)
                return 
                call<idx + 1>(
                    static_cast<decltype(__calls)&&>(__calls), 
                    static_cast<decltype(__args)&&>(__args)) ;
            else 
            {    
                auto&& __res = std::apply(__call, static_cast<decltype(__args)&&>(__args)) ;
                return 
                    std::tuple_cat(
                        std::make_tuple(__res), 
                        call<idx + 1>(
                            static_cast<decltype(__calls)&&>(__calls), 
                            std::tuple_cat(
                                static_cast<decltype(__args)&&>(__args), 
                                std::make_tuple(__res)))) ; 
            }
        }
        else 
            return std::make_tuple() ;

    }


    struct test
    {
        constexpr auto
        interpret(
            given_node<auto> const& __given, 
            when_node<auto> const& __when,
            then_node<auto> const& __then)
        {        
            // tuple of args
            auto&& __args = std::apply(
                    [](auto&&... __acts) { return std::make_tuple(__acts()...) ; },
                     __given.act()) ;

            // tuple of results 
            auto&& __results = __call<0>(__when.act(), static_cast<decltype(__args)&&>(__args)) ; 

            // tuple of assertions results
            std::apply([](auto&&... __ress){([](auto&& __res){std::cout << __res << std::endl;}(__ress), ...) ;}, __results);

            auto&& __assertsres = std::apply(
                [&__results] (auto&& ... __assert) { return std::make_tuple(std::apply(__assert, __results)...) ; } , 
                __then.act()) ;
     
            return 
            std::apply(
                [] (auto&& ... __assres) { return (__assres && ...) ; }, 
                __assertsres ) ;
        }
    } ; 
}

#endif