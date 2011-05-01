#ifndef MPLLIBS_ERROR_LETREC_H
#define MPLLIBS_ERROR_LETREC_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/error/let.h>

namespace mpllibs
{
  namespace error
  {
    template <class A, class E1, class E2>
    struct letrec : let<A, letrec<A, E1, E1>, E2> {};
  }
}

#endif

