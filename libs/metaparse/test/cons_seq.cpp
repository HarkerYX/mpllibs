// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/util/cons_seq.hpp>

#include "common.hpp"

#include <mpllibs/metatest/test.hpp>
#include <mpllibs/metatest/has_type.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/deque.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/equal.hpp>

using mpllibs::metatest::suite_path;
using mpllibs::metatest::has_type;

using mpllibs::metaparse::util::cons_seq;

using boost::mpl::equal;
using boost::mpl::apply_wrap1;
using boost::mpl::list;
using boost::mpl::deque;

namespace
{
  const suite_path suite = suite_path("util")("cons_seq");
  
  typedef has_type<cons_seq> test_has_type;

  typedef
    equal<
      apply_wrap1<cons_seq, deque<int11, list<int13> > >::type,
      list<int11, int13>
    >
    test_pushing_to_list;

  typedef
    equal<
      apply_wrap1<cons_seq, deque<int13, empty_list> >::type,
      list<int13>
    >
    test_pushing_to_empty_list;
}

MPLLIBS_ADD_TEST(suite, test_has_type)
MPLLIBS_ADD_TEST(suite, test_pushing_to_list)
MPLLIBS_ADD_TEST(suite, test_pushing_to_empty_list)
