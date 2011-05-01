// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/iterate.h>
#include <mpllibs/metaparse/is_error.h>
#include <mpllibs/metaparse/source_position.h>
#include <mpllibs/metaparse/get_result.h>

#include "common.h"

#include <mpllibs/metatest/test.h>
#include <mpllibs/metatest/test_suite.h>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/equal.hpp>

using mpllibs::metatest::test_suite;

using mpllibs::metaparse::is_error;
using mpllibs::metaparse::iterate;
using mpllibs::metaparse::one_char;
using mpllibs::metaparse::start;
using mpllibs::metaparse::get_result;

using boost::mpl::apply;
using boost::mpl::equal;
using boost::mpl::list;

namespace
{
  const test_suite suite("iterate");

  typedef
    is_error<apply<iterate<one_char, int13>, str_, start> >
    test_empty_input;

  typedef
    equal<
      get_result<apply<iterate<one_char, int0>, str_hello, start> >::type,
      list<>
    >
    test0;

  typedef
    equal<
      get_result<apply<iterate<one_char, int1>, str_hello, start> >::type,
      list<char_h>
    >
    test1;

  typedef
    equal<
      get_result<apply<iterate<one_char, int2>, str_hello, start> >::type,
      list<char_h, char_e>
    >
    test2;

  typedef
    equal<
      get_result<apply<iterate<one_char, int3>, str_hello, start> >::type,
      list<char_h, char_e, char_l>
    >
    test3;
}

MPLLIBS_ADD_TEST(suite, test_empty_input)
MPLLIBS_ADD_TEST(suite, test0)
MPLLIBS_ADD_TEST(suite, test1)
MPLLIBS_ADD_TEST(suite, test2)
MPLLIBS_ADD_TEST(suite, test3)

