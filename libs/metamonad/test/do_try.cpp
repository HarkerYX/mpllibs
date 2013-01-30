// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metamonad/do_try.hpp>
#include <mpllibs/metamonad/exception.hpp>
#include <mpllibs/metamonad/tmp_tag.hpp>
#include <mpllibs/metamonad/tmp_value.hpp>
#include <mpllibs/metamonad/syntax.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/plus.hpp>

#include <boost/type_traits/is_same.hpp>

#include "common.hpp"

using mpllibs::metamonad::tmp_tag;
using mpllibs::metamonad::tmp_value;

namespace
{
  struct tag1 : tmp_tag<tag1> {};
  struct e1 : tmp_value<e1, tag1> {};
  
  struct tag2 : tmp_tag<tag2> {};
  struct e2 : tmp_value<e2, tag2> {};
  
  struct t1 : tmp_value<t1> {};
  struct t2 : tmp_value<t2> {};
}

BOOST_AUTO_TEST_CASE(test_do_try)
{
  using boost::mpl::equal_to;
  using boost::mpl::identity;
  using boost::mpl::tag;
  using boost::mpl::plus;
  
  using mpllibs::metamonad::exception;
  using mpllibs::metamonad::catch_any;
  using mpllibs::metamonad::do_try;
  using mpllibs::metamonad::set;
  using mpllibs::metamonad::do_return;
  using mpllibs::metamonad::syntax;

  using mpllibs::metatest::meta_require;

  meta_require<
    equal_to<
      int13,
      do_try<
        syntax<do_return<int13> >
      >
      ::catch_<tag1, x>
        ::apply<syntax<int11> >
      ::type
    >
  >(MPLLIBS_HERE, "test_no_exception");

  meta_require<
    equal_to<
      int2,
      do_try<
        syntax<set<t1, int1> >,
        syntax<set<t2, int1> >,
        syntax<plus<t1, t2> >
      >::type
    >
  >(MPLLIBS_HERE, "test_no_exception_no_catch");

  meta_require<
    equal_to<
      int11,
      do_try<
        syntax<exception<e1> >
      >
      ::catch_<tag1, x>
        ::apply<syntax<identity<int11> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_catch");

  meta_require<
    equal_to<
      int13,
      do_try<
        syntax<exception<int13> >
      >
      ::catch_<tag<int13>::type, x>
        ::apply<syntax<identity<x> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_exception_value_in_catch");

  meta_require<
    equal_to<
      exception<int13>,
      do_try<
        syntax<exception<int13> >
      >
      ::catch_<tag2, x>
        ::apply<syntax<identity<int11> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_not_catching");

  meta_require<
    equal_to<
      int13,
      do_try<
        syntax<exception<e2> >
      >
      ::catch_<tag1, x>
        ::apply<syntax<identity<int11> > >
      ::catch_<tag2, x>
        ::apply<syntax<identity<int13> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_second_catch");

  meta_require<
    equal_to<
      int11,
      do_try<
        syntax<exception<e1> >,
        syntax<do_return<int1> >
      >
      ::catch_<tag1, x>
        ::apply<syntax<identity<int11> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_exception_propagation");


  meta_require<
    equal_to<
      int11,
      do_try<
        syntax<do_return<int13> >,
        syntax<do_return<int11> >
      >
      ::catch_<tag1, x>
        ::apply<syntax<identity<int11> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_execution_sequence");
  
  meta_require<
    equal_to<
      int11,
      do_try<
        syntax<set<x, exception<e1> > >,
        syntax<do_return<int1> >
      >
      ::catch_<tag1, x>
        ::apply<syntax<identity<int11> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_exception_in_set");

  meta_require<
    equal_to<
      int13,
      do_try<
        syntax<exception<e1> >,
        syntax<do_return<int1> >
      >
      ::catch_<catch_any, x>
        ::apply<syntax<identity<int13> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_catch_any");

  meta_require<
    equal_to<
      exception<int13>,
      do_try<
        syntax<exception<e1> >,
        syntax<do_return<int1> >
      >
      ::catch_<catch_any, x>
        ::apply<syntax<exception<int13> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_rethrowing");

  meta_require<
    equal_to<
      exception<int13>,
      do_try<
        syntax<exception<e1> >,
        syntax<do_return<int1> >
      >
      ::catch_<catch_any, x>
        ::apply<syntax<exception<int13> > >
      ::catch_<catch_any, x>
        ::apply<syntax<exception<int13> > >
      ::type
    >
  >(MPLLIBS_HERE, "test_rethrowing_not_caught_by_next_catch");
}

