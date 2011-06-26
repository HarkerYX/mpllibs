#ifndef MPLLIBS_METAPARSE_GET_LINE_HPP
#define MPLLIBS_METAPARSE_GET_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metatest/to_stream_fwd.hpp>

#include <boost/mpl/tag.hpp>

#include <iostream>

namespace mpllibs
{
  namespace metaparse
  {
    template <class P>
    struct get_line_impl;
    
    template <class P>
    struct get_line :
      get_line_impl<typename boost::mpl::tag<typename P::type>::type>::
        template apply<typename P::type>
    {};
  }
}

MPLLIBS_DEFINE_TO_STREAM_FOR_TEMPLATE(
  1,
  mpllibs::metaparse::get_line,
  "get_line"
);

#endif

