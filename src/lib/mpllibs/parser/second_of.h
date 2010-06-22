#ifndef MPLLIBS_PARSER_SECOND_OF_H
#define MPLLIBS_PARSER_SECOND_OF_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/parser/transform.h>
#include <mpllibs/parser/sequence.h>

#include <boost/mpl/quote.hpp>

namespace mpllibs
{
  namespace parser
  {
    template <class p1, class p2>
    struct second_of :
      mpllibs::parser::transform<
        mpllibs::parser::sequence<p1, p2>,
        boost::mpl::quote1<boost::mpl::second>
      >
    {};
  }
}

#endif
