#ifndef MPLLIBS_PARSER_ITERATE_H
#define MPLLIBS_PARSER_ITERATE_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/parser/one_char.h>
#include <mpllibs/parser/sequence.h>
#include <mpllibs/parser/return.h>
#include <mpllibs/parser/transform.h>

#include <mpllibs/util/cons.h>

#include <boost/mpl/list.hpp>
#include <boost/mpl/int.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/minus.hpp>

namespace mpllibs
{
  namespace parser
  {
    template <class p, class n>
    struct iterate :
      boost::mpl::if_<
        typename boost::mpl::equal_to<n, boost::mpl::int_<0> >::type,
        mpllibs::parser::return_<boost::mpl::list<> >,
        mpllibs::parser::transform<
         typename mpllibs::parser::sequence<
            p,
            typename mpllibs::parser::iterate<
              p,
              typename boost::mpl::minus<n, boost::mpl::int_<1> >::type
            >
          >,
          mpllibs::util::cons
        >
      >::type
    {};
  }
}

#endif
