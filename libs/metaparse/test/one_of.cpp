// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/one_of.hpp>
#include <mpllibs/metaparse/one_char.hpp>
#include <mpllibs/metaparse/fail.hpp>
#include <mpllibs/metaparse/is_error.hpp>
#include <mpllibs/metaparse/start.hpp>
#include <mpllibs/metaparse/get_result.hpp>
#include <mpllibs/metaparse/sequence.hpp>
#include <mpllibs/metaparse/get_position.hpp>
#include <mpllibs/metaparse/next_char.hpp>

#include "common.hpp"

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_one_of)
{
  using mpllibs::metaparse::is_error;
  using mpllibs::metaparse::one_of;
  using mpllibs::metaparse::start;
  using mpllibs::metaparse::get_result;
  using mpllibs::metaparse::one_char;
  using mpllibs::metaparse::fail;
  using mpllibs::metaparse::sequence;
  using mpllibs::metaparse::get_position;
  using mpllibs::metaparse::next_char;
  
  using boost::mpl::apply_wrap2;
  using boost::mpl::equal_to;
  
  typedef fail<test_failure> test_fail;
  typedef sequence<one_char, test_fail> test_fail_later;

  // test_1_with_good
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<apply_wrap2<one_of<one_char>, str_hello, start> >::type,
      char_h
    >
  ));

  // test_1_with_bad
  BOOST_MPL_ASSERT((
    is_error<apply_wrap2<one_of<test_fail>, str_hello, start> >
  ));

  // test_2_with_two_good
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<
        apply_wrap2<one_of<one_char, one_char>, str_hello, start>
      >::type,
      char_h
    >
  ));

  // test_2_with_first_good
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<
        apply_wrap2<one_of<one_char, test_fail>, str_hello, start>
      >::type,
      char_h
    >
  ));

  // test_2_with_second_good
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<
        apply_wrap2<one_of<test_fail, one_char>, str_hello, start>
      >::type,
      char_h
    >
  ));

  // test_2_with_two_bad
  BOOST_MPL_ASSERT((
    is_error<apply_wrap2<one_of<test_fail, test_fail>, str_hello, start> >
  ));





  // test
  BOOST_MPL_ASSERT((is_error<apply_wrap2<one_of< >, str_hello, start> >));
  
  // test_with_good
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<apply_wrap2<one_of<one_char>, str_hello, start> >::type,
      char_h
    >
  ));
  
  // test_with_bad
  BOOST_MPL_ASSERT((is_error<apply_wrap2<one_of<test_fail>,str_hello,start> >));

  // test_with_two_good
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<
        apply_wrap2<one_of<one_char, one_char>, str_hello, start>
      >::type,
      char_h
    >
  ));
    
  // test_with_first_good
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<
        apply_wrap2<one_of<one_char, test_fail>, str_hello, start>
      >::type,
      char_h
    >
  ));

  // test_with_second_good
  BOOST_MPL_ASSERT((
    equal_to<
      get_result<
        apply_wrap2<one_of<test_fail, one_char>, str_hello, start>
      >::type,
      char_h
    >
  ));

  // test_with_two_bad
  BOOST_MPL_ASSERT((
    is_error<apply_wrap2<one_of<test_fail, test_fail>, str_hello, start> >
  ));

  // test_error_is_the_last_error
  BOOST_MPL_ASSERT((
    equal_to<
      next_char<start, char_h>::type,
      get_position<
        apply_wrap2<
          one_of<test_fail, test_fail_later>,
          str_hello,
          start
        >
      >::type
    >
  ));
}


