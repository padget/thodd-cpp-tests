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


    extern constexpr auto given = 
        [](auto&&... __ctxs)
        { 
            return 
            as_dsl_node([=] { }) ;
        } ; 

    extern constexpr auto when = 
        [] (auto&&... __actions) 
        { 
            return
            as_dsl_node([=] { }) ;
         } ;

    extern constexpr auto then = 
        [](auto&&... __asserts)
        { 
            return
            as_dsl_node([=] { }) ;
        } ;

    constexpr auto toot = given("coucou", "kiki") > when("poutou") > then("toto") ;
}
 
#endif