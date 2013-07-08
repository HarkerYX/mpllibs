# iterate_c

## Synopsis

```cpp
template <class P, int N>
struct iterate_c
{
  template <class S, class Pos>
  struct apply
  {
    // unspecified
  };
};
```

## Description

Parser combinator taking a parser and an integer as arguments.
It applies the parser on the input string `N` times. The result of parsing
is a sequence of the results of the individual applications of the parser.
`P` has to accept the input `N` times for `iterate_c` to accept it.

## Header

```cpp
#include <mpllibs/metaparse/iterate_c.hpp>
```

## Expression semantics

For any `p` parser, `n` integer value the following are equivalent:

```cpp
iterate_c<p, n>

mpllibs::metaparse::sequence<
  p, // 1.
  p, // 2.
  // ...
  p  // n.
>
```

## Example

```cpp
typedef iterate_c<mpllibs::metaparse::one_char, 3> three_chars;
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)


