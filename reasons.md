# Why `exceptions4c`? #

As you can see, there are [other exception handling systems](alternatives.md) for C. Nevertheless, there are many reasons for choosing `exceptions4c`; here you have just `1000` one of them:

  * ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/free_software.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/free_software.png) `000`: **[Free Software](#Free_Software.md)**
  * ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/simple_api.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/simple_api.png) `001`: **[Simple API](#Simple_API.md)**
  * ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/ansi_c.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/ansi_c.png) `010`: **[ANSI C](#ANSI_C.md)**
  * ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/safe.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/safe.png) `011`: **[Safe](#Safe.md)**
  * ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/portable.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/portable.png) `100`: **[Portable](#Portable.md)**
  * ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/no_compilation_warnings.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/no_compilation_warnings.png) `101`: **[No Compilation Warnings](#No_Compilation_Warnings.md)**
  * ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/statically_checked.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/statically_checked.png) `110`: **[Statically Checked](#Statically_Checked.md)**
  * ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/beautifully_crafted.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/beautifully_crafted.png) `111`: **[Beautifully Crafted](#Beautifully_Crafted.md)**

You may also be interested in the `1000` [features](features.md) of the library.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/free_software.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/free_software.png) Free Software #

`exceptions4c` is released under the [GNU LGPL](http://www.gnu.org/licenses/lgpl.html) in the hope that it will encourage free software development. In case you haven't heard about free software yet, you should know **it is a matter of freedom, not price**.

As with any free software, you are entitled to use this library for any purpose. You can also study how it works, and change it to make it do what you wish. You have the freedom to redistribute it, improve it, and release your improvements to the public, so that the whole community benefits.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/simple_api.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/simple_api.png) Simple API #

The API is designed to be easy to use and intuitive. Its semantics are analogous to those of other exception handling systems. **`exceptions4c` will feel natural to any programmer who has experience with languages that support exceptions natively**.

`exceptions4c` will not stand in your way; most library functionalities are accessed through `keywords` introducing a block of code. For example, you write: `try{ /* this */ }` or: `finally{ /* that */ }` so your program does not get cluttered with error handling code.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/ansi_c.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/ansi_c.png) ANSI C #

The library is written in plain ANSI C and conforms to the ISO/IEC 9899:1990 standard (commonly referred to as C89 or C90). It does not rely on any non-ANSI extensions. **Programs you write using `exceptions4c` can be ANSI compliant**.

In order to avoid namespace conflicts, exported functions and variables have the prefix e4c_, and exported macros have the prefix E4C_. The only exported entities that do not follow this rule are: _keywords_ (such as `try` or `catch`) and predefined exceptions (such as `NullPointerException` or `NotEnoughMemoryException`).


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/safe.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/safe.png) Safe #

While `exceptions4c` adheres to the C89 standard, the author is well aware that there are quite a few _unsafe_ functions in it. Moreover, these functions have their _safe_ counterpart in the C99 standard. For example, `snprintf` is a buffer-safe version of `sprintf`, etc.

In order to achieve safety while mantaining backwards compatibility, `exceptions4c` provides two implementations. One of them uses the _unsafe_ functions from the C89 standard. The other one **uses the _safe_ functions from the C99 standard, via conditional compilation**. This allows the library to take advantage of newer compilers on those platforms which support them.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/portable.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/portable.png) Portable #

`exceptions4c` has no library dependencies. It uses nothing but standard C functions, and should compile using any ANSI compliant compiler. The library includes standard headers only: `stdlib.h`, `stdio.h`, `stdarg.h`, `setjmp.h`, `signal.h` and `errno.h`. If you want to use `exceptions4c`, **you just need to drop `e4c.h` and `e4c.c` into your project** and `#include "e4c.h"` from your sorce code. That's all.

The library can be customized via conditional compilation to fit your needs. For example, if you don't want the _keywords_ `try`, `catch` etc. to be defined, you could set `E4C_NOKEYWORDS` on. There are also other compile-time parameters, such as: `NDEBUG`, `E4C_THREADSAFE`, `E4C_FUNCTION_NAME_`, `E4C_INVALID_SIGNAL_NUMBER_` and `E4C_NORETURN_`.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/no_compilation_warnings.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/no_compilation_warnings.png) No Compilation Warnings #

Nobody likes compiler warnings. However, while some people seem to be happy just by ignoring them, disciplined programmers prefer to get rid of them properly. If you are one of them, you'll love to know that **`exceptions4c` can be compiled with all warnings enabled**, at the compiler's most _pedantic_ setting.

For example, if you are using `gcc` you can set these flags on: `-Wall -Wextra -pedantic`. The library (and the testing framework) will compile with these setting without warnings.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/statically_checked.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/statically_checked.png) Statically Checked #

In addition to compiling without warnings, **`exceptions4c` is also checked with [Splint](http://www.splint.org/)** (a static source code analyzer) **and passes with zero warnings**.

All source code is annotated with _stylized comments_ that document assumptions about functions, variables, parameters and types. This means that the semantics of the library are completely defined in terms of Splint annotations.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/beautifully_crafted.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/beautifully_crafted.png) Beautifully Crafted #

To me, `exceptions4c` is a really fun project to develop. **This library is for coders who enjoy programming in C** and want to improve the way they detect and handle errors in their applications.

The library also takes into account real-world platforms on which it will be compiled and run. For example:

  * If your compiler is C99 compliant, then the library will support the newer features: variadic macros, buffer safe functions, the standard `bool` type, etc.
  * If your platform is POSIX compliant, then the library will use the functions `sigsetjmp` and `siglongjmp` (instead of `setjmp` and `longjmp`).
  * If the library detects that you are using `pthreads`, it will ask you to enable its thread-safe version.

There are also other goodies, such as a packaged extension (DevPak) and a compiled HTML (CHM) version of the documentation.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)