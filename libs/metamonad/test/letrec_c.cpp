// Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metamonad/letrec_c.hpp>
#include <mpllibs/metamonad/lambda_c.hpp>
#include <mpllibs/metamonad/eval_syntax.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

#include "common.hpp"

#include <boost/mpl/minus.hpp>

BOOST_AUTO_TEST_CASE(test_letrec_c)
{
  using mpllibs::metatest::meta_require;

  using boost::mpl::equal_to;
  using boost::mpl::minus;
  using boost::mpl::eval_if;
  
  using mpllibs::metamonad::letrec_c;
  using mpllibs::metamonad::lambda_c;
  using mpllibs::metamonad::lazy;
  using mpllibs::metamonad::eval_syntax;

  // name is replaced with a nullary metafunction evaluating to the
  // substituted expression
  meta_require<
    equal_to<int13, eval_syntax<letrec_c<x, int13, x> >::type>
  >(MPLLIBS_HERE, "test_letrec_name");

  meta_require<
    equal_to<int11, eval_syntax<letrec_c<x, int13, int11> >::type>
  >(MPLLIBS_HERE, "test_letrec_not_name");
  
  meta_require<
    equal_to<
      int26,
      eval_syntax<letrec_c<x, int13, lazy_double_value<x> > >::type
    >
  >(MPLLIBS_HERE, "test_template");

  meta_require<
    equal_to<
      int24,
      eval_syntax<
        letrec_c<x, int13, eval_syntax<letrec_c<y, int11, lazy_plus<x, y> > > >
      >::type
    >
  >(MPLLIBS_HERE, "test_nested_letrec");
  
  meta_require<
    equal_to<
      int37,
      eval_syntax<
        letrec_c<
          x, int13,
          double_lazy_plus<
            x,
            eval_syntax<letrec_c<x, int11, lazy_plus<x, int13> > >
          >
        >
      >::type
    >
  >(MPLLIBS_HERE, "test_shadowing");
  
  meta_require<
    equal_to<
      int24,
      eval_syntax<
        letrec_c<
          x,
          lambda_c<
            y,
            eval_if<
              lazy_equal_to<y, int0>,
              int1,
              lazy_times<lazy_apply<x, minus<y, int1> >, y>
            >
          >,
          lazy_apply<x, int4>
        >
      >::type
    >
  >(MPLLIBS_HERE, "test_recursion");

  meta_require<
    equal_to<
      int11,
      eval_syntax<letrec_c<x, int2, lazy<minus<int13, x> > > >::type
    >
  >(MPLLIBS_HERE, "test_letrec_lazy");
}


