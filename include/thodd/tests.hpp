#ifndef __THODD_TESTS_TESTS_HPP__
#  define  __THODD_TESTS_TESTS_HPP__ 

#  include <tuple>
#  include <type_traits>

#  include <thodd/dsl.hpp>

namespace
thodd
{ 
    // given().an_egg().
    //     and().some_milk().
    //     and().the_ingredient( "flour" );
    // when().the_cook_mangles_everything_to_a_dough().
    //     and().the_cook_fries_the_dough_in_a_pan();
    // then().the_resulting_meal_is_a_pancake();

    /* 
    given(ann_egg, some_milk, the_ingredient("flour"))
    > when(the_cook_mangles_everything_to_a_dough, 
           the_cook_fries_the_dough_in_a_pan)
    > then(the_resulting_meal_is_a_pancake)

    given(
        []{return egg();}, 
        []{return milk();}, 
        [](auto&& __name){return [=__name]{return __name;}; })
    > when([](auto&&... __ingres){return __ingres +...;})
    > then([](auto&& __res){return __res == 2});
*/

    enum class tests
    {
        given, 
        when, 
        then
    } ;

    extern constexpr auto given = 
        [](auto&&... __ctxs)
        { 
            return 
            as_dsl_node(
                std::integral_constant<tests, tests::given>{}, 
                [=] { }) ;
        } ; 

    extern constexpr auto when = 
        [] (auto&&... __actions) 
        { 
            return
            as_dsl_node(
                std::integral_constant<tests, tests::when>{},
                [=] { }) ;
         } ;

    extern constexpr auto then = 
        [](auto&&... __asserts)
        { 
            return
            as_dsl_node(
                std::integral_constant<tests, tests::then>{},
                [=] { }) ;
        } ;

    constexpr auto toot = given("coucou", "kiki") > when("poutou") > then("toto") ;

    template<
        typename ... givens_t>
    constexpr int 
    interpret(
        dsl_node<tests, tests::given, auto> const & __given, 
        dsl_node<tests, tests::when, auto> const & __when, 
        dsl_node<tests, tests::then, auto> const & __then)
    {
        return 2 ;
    }

    constexpr auto i = interpret(given(), when(), then()) ;
}
 
#endif