#ifndef MPLLIBS_PARSER_ALWAYS_H
#define MPLLIBS_PARSER_ALWAYS_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/return.h>
#include <mpllibs/metaparse/is_error.h>
#include <mpllibs/metaparse/get_remaining.h>
#include <mpllibs/metaparse/get_position.h>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>

namespace mpllibs
{
  namespace metaparse
  {
    template <class P, class Result>
    struct always
    {
    private:
      template <class Res>
      struct apply_unchecked :
        boost::mpl::apply<
          return_<Result>,
          typename get_remaining<Res>::type,
          typename get_position<Res>::type
        >
      {};
    public:
      template <class S, class Pos>
      struct apply :
        boost::mpl::eval_if<
          typename is_error<boost::mpl::apply<P, S, Pos> >::type,
          boost::mpl::apply<P, S, Pos>,
          apply_unchecked<boost::mpl::apply<P, S, Pos> >
        >
      {};
    };
  }
}

#endif

