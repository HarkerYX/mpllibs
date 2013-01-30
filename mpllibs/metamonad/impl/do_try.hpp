#ifndef MPLLIBS_METAMONAD_IMPL_DO_TRY_HPP
#define MPLLIBS_METAMONAD_IMPL_DO_TRY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metamonad/eval_let_c.hpp>
#include <mpllibs/metamonad/exception.hpp>
#include <mpllibs/metamonad/tmp_value.hpp>
#include <mpllibs/metamonad/metafunction.hpp>
#include <mpllibs/metamonad/returns.hpp>
#include <mpllibs/metamonad/lambda.hpp>
#include <mpllibs/metamonad/name.hpp>
#include <mpllibs/metamonad/lazy.hpp>
#include <mpllibs/metamonad/lazy_protect_args.hpp>
#include <mpllibs/metamonad/already_lazy.hpp>
#include <mpllibs/metamonad/eval_match_let.hpp>
#include <mpllibs/metamonad/case.hpp>
#include <mpllibs/metamonad/make_syntax.hpp>

#include <mpllibs/metatest/to_stream_fwd.hpp>

#include <boost/mpl/tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>

#include <boost/type_traits/is_same.hpp>

/*
 * Catching exceptions happens by using
 *   do_try<...>
 *     ::catch_<Tag1, Name1>
 *       ::apply<Body1>
 *     ::catch_<Tag2, Name2>
 *       ::apply<Body2>
 * instead of
 *   do_try<...>
 *     ::catch_<Tag1, Name1, Body1>
 *     ::catch_<Tag2, Name2, Body2>
 * to avoid ambiguity related to
 *  http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#147
 * caused by do_try<...>::catch_<...>::catch_<...> patterns.
 */

namespace mpllibs
{
  namespace metamonad
  {
    struct catch_any : tmp_value<catch_any> {};

    namespace impl
    {
      // evaluates result lazily
      template <class Result>
      struct skip_further_catches : returns<typename Result::type>
      {
        MPLLIBS_METAFUNCTION(catch_, (ExceptionTag)(Name))
        ((lambda_c<_, skip_further_catches>));

        MPLLIBS_METAFUNCTION(catch_c, (ExceptionTag)(Name))
        ((lambda_c<_, skip_further_catches>));
      };

      template <class Exception>
      struct was_exception : returns<typename Exception::type>
      {
        template <class ExceptionTag, class Name>
        struct catch_ : tmp_value<catch_<ExceptionTag, Name> >
        {
          template <class Body>
          struct apply :
            eval_match_let<
              syntax<exception<d> >, typename Exception::type,
              syntax<
                lazy<
                  boost::mpl::if_<
                    boost::mpl::or_<
                      boost::is_same<
                        already_lazy<ExceptionTag>,
                        boost::mpl::tag<already_lazy<d> >
                      >,
                      lazy_protect_args<
                        boost::is_same<ExceptionTag, catch_any>
                      >
                    >,
                    already_lazy<
                      skip_further_catches<
                        eval_let<Name, make_syntax<d>, Body>
                      >
                    >,
                    already_lazy<was_exception>
                  >
                >
              >
            >::type
          {};
        };

        template <class ExceptionTag, class Name>
        struct catch_c : tmp_value<catch_c<ExceptionTag, Name> >
        {
          template <class Body>
          struct apply :
            was_exception<Exception>::template apply<syntax<Body> >
          {};
        };
      };

      template <class Do>
      struct do_try_impl :
        eval_syntax<
          eval_let_c<
            r, Do,
            case_< r,
              matches_c<
                exception<_>,
                returns<mpllibs::metamonad::impl::was_exception<r> >
              >,
              matches_c<_,
                returns<mpllibs::metamonad::impl::skip_further_catches<r> >
              >
            >
          >
        >::type
      {};
    }
  }
}

#endif

