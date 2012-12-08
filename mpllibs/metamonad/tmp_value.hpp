#ifndef MPLLIBS_METAMONAD_TMP_VALUE_HPP
#define MPLLIBS_METAMONAD_TMP_VALUE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metatest/to_stream_fwd.hpp>

namespace mpllibs
{
  namespace metamonad
  {
    template <class T>
    struct tmp_value
    {
      typedef T type;
    };
  }
}

MPLLIBS_DEFINE_TO_STREAM_FOR_TEMPLATE(
  1,
  mpllibs::metamonad::tmp_value,
  "tmp_value"
)

#endif

