#ifndef MPLLIBS_PARSER_ITERATE_H
#define MPLLIBS_PARSER_ITERATE_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/iterate_c.h>

namespace mpllibs
{
  namespace metaparse
  {
    template <class P, class N>
    struct iterate : iterate_c<P, N::type::value> {};
  }
}

#endif

