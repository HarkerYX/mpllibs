# DebugParsingError

## Synopsis

```cpp
template <class Parser, class String>
struct debug_parsing_error
{
  debug_parsing_error()
  {
    // unspecified
  }
  
  // unspecified
};
```

## Description

Utility to debug errors generated by a compile-time parser. This is a template
class taking two arguments, the parser and an input string. An instance of the
instantiated template class has to be created and initialised using the default
constructor. When parsing the input string using the parser generates an error,
the default constructor of `debug_parsing_error` prints the error message to the
standard output at run-time and calls `exit`.

## Header

```cpp
#include <mpllibs/metaparse/debug_parsing_error.hpp>
```

## Expression semantics

For any `p` compile-time parser and `s` compile-time string

```cpp
debug_parsing_error<p, s>()
```

Tries to parse `s` using `p` at compile-time. At run-time the constructor
prints the result of parsing to the standard output and calls `exit`.

## Example

```cpp
debug_parsing_error<some_parser, boost::string<'abcd'>> do_debugging;
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)


