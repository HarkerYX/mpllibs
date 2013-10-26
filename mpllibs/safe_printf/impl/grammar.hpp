#ifndef MPLLIBS_SAFE_PRINTF_IMPL_GRAMMAR_HPP
#define MPLLIBS_SAFE_PRINTF_IMPL_GRAMMAR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/safe_printf/impl/any_type.hpp>
#include <mpllibs/safe_printf/error.hpp>

#include <mpllibs/metaparse/always.hpp>
#include <mpllibs/metaparse/any.hpp>
#include <mpllibs/metaparse/any1.hpp>
#include <mpllibs/metaparse/digit.hpp>
#include <mpllibs/metaparse/except.hpp>
#include <mpllibs/metaparse/first_of.hpp>
#include <mpllibs/metaparse/last_of.hpp>
#include <mpllibs/metaparse/lit_c.hpp>
#include <mpllibs/metaparse/one_char.hpp>
#include <mpllibs/metaparse/one_of.hpp>

#include <mpllibs/metamonad/box.hpp>

#include <string>

namespace mpllibs
{
  namespace safe_printf
  {
    namespace impl
    {
      namespace grammar
      {
        using mpllibs::metaparse::any;
        using mpllibs::metaparse::any1;
        using mpllibs::metaparse::always;
        using mpllibs::metaparse::digit;
        using mpllibs::metaparse::except;
        using mpllibs::metaparse::first_of;
        using mpllibs::metaparse::last_of;
        using mpllibs::metaparse::lit_c;
        using mpllibs::metaparse::one_char;
        using mpllibs::metaparse::one_of;
        using mpllibs::metaparse::return_;
        using mpllibs::metaparse::sequence;

        using mpllibs::metamonad::box;

        using boost::mpl::true_;
        using boost::mpl::false_;

        typedef
          any<
            one_of<
              last_of<lit_c<'%'>, lit_c<'%'> >,
              last_of<
                except<
                  lit_c<'%'>,
                  boost::mpl::void_,
                  error::no_percentage_char_expected
                >,
                one_char
              >
            >
          >
          normal_chars;

        typedef
          one_of<lit_c<'-'>, lit_c<'+'>, lit_c<' '>, lit_c<'#'>, lit_c<'0'> >
          flag;

        typedef any1<digit> integer;
      
        // Returns true_ or false_
        typedef
          one_of<
            always<integer, false_>,
            always<lit_c<'*'>, true_>,
            return_<false_>
          >
          width;

        // Returns true_ or false_
        typedef one_of<last_of<lit_c<'.'>, width>, return_<false_> > precision;

        typedef
          one_of<
            always<lit_c<'c'>, box<char> >,
            always<one_of<lit_c<'d'>, lit_c<'i'> >, box<int> >,
            always<
              one_of<
                lit_c<'e'>,
                lit_c<'E'>,
                lit_c<'f'>,
                lit_c<'g'>,
                lit_c<'G'>
              >,
              box<double>
            >,
            always<lit_c<'o'>, box<int> >,
            always<lit_c<'s'>, box<char*> >,
            always<
              one_of<lit_c<'u'>, lit_c<'x'>, lit_c<'X'> >,
              box<unsigned int>
            >,
            always<lit_c<'p'>, box<any_type*> >,
            always<lit_c<'n'>, box<int*> >
          >
          format_no_flag;

        typedef
          one_of<
            always<
              one_of<lit_c<'d'>, lit_c<'i'>, lit_c<'o'> >,
              box<short int>
            >,
            always<
              one_of<lit_c<'u'>, lit_c<'x'>, lit_c<'X'> >,
              box<short unsigned int>
            >
          >
          format_h_flag;

        typedef
          one_of<
            always<lit_c<'c'>, box<wchar_t> >,
            always<one_of<lit_c<'d'>, lit_c<'i'>, lit_c<'o'> >, box<long int> >,
            always<lit_c<'s'>, box<wchar_t*> >,
            always<
              one_of<lit_c<'u'>, lit_c<'x'>, lit_c<'X'> >,
              box<long unsigned int>
            >
          >
          format_l_flag;

        typedef
          always<
            one_of<lit_c<'e'>, lit_c<'E'>, lit_c<'f'>, lit_c<'g'>, lit_c<'G'> >,
            box<long double>
          >
          format_capital_l_flag;

        typedef
          one_of<
            last_of<lit_c<'h'>, format_h_flag>,
            last_of<lit_c<'l'>, format_l_flag>,
            last_of<lit_c<'L'>, format_capital_l_flag>,
            format_no_flag
          >
          format;

        // returns deque<defined extra int, defined extra int, format>
        typedef
          last_of<lit_c<'%'>, any<flag>, sequence<width, precision, format> >
          parameter;

        typedef
          last_of<normal_chars, any<first_of<parameter, normal_chars> > >
          S;
      }
    }
  }
}

#endif

