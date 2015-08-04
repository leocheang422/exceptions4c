**Exceptions for C**: bring the power of exceptions to your C applications with this tiny, portable library.

<img src='http://exceptions4c.googlecode.com/svn/trunk/etc/img/example.png' alt='exceptions4c' width='512' height='512' />


---


# An exception handling framework for C #

This library provides you with a simple set of keywords (_macros_, actually) which map the semantics of exception handling you're probably already used to:
  * **`try`**
  * **`catch`**
  * **`finally`**
  * **`throw`**

You can use exceptions in C by writing `try/catch/finally` blocks:

```

#include "e4c.h"

int foobar(){

    int foo;
    void * buffer = malloc(1024);

    if(buffer == NULL){
        throw(NotEnoughMemoryException, "Could not allocate buffer.");
    }

    try{
        foo = get_user_input(buffer, 1024);
    }catch(BadUserInputException){
        foo = 123;
    }finally{
        free(buffer);
    }

    return(foo);
}

```

This way you will never have to deal again with boring error codes, or check return values every time you call a function.

# Exception Hierarchies #

The possible exceptions in a program are organized in a _pseudo-hierarchy_ of exceptions. `RuntimeException` is the root of the exceptions _pseudo-hierarchy_. **Any** exception can be caught by a `catch(RuntimeException)` block, **except** `AssertionException`.

When an exception is thrown, control is transferred to the nearest dynamically-enclosing `catch` code block that handles the exception. Whether a particular `catch` block handles an exception is found out by comparing the type (and supertypes) of the actual thrown exception against the specified exception in the `catch` clause.

A `catch` block is given an exception as a parameter. This parameter determines the set of exceptions that can be handled by the code block. A block handles an actual exception that was thrown if the specified parameter is either:
  * the same type of that exception.
  * the same type of any of the _supertypes_ of that exception.

If you write a `catch` block that handles an exception with no defined _subtype_, it will only handle that very specific exception. By grouping exceptions in _hierarchies_, you can design generic `catch` blocks that deal with several exceptions:

```

/*
                 name             default message             supertype
*/
E4C_DEFINE_EXCEPTION(ColorException, "This is a colorful error.", RuntimeException);
E4C_DEFINE_EXCEPTION(RedException,   "This is a red error.",      ColorException);
E4C_DEFINE_EXCEPTION(GreenException, "This is a green error.",    ColorException);
E4C_DEFINE_EXCEPTION(BlueException,  "This is a blue error.",     ColorException);

...

try{
    int color = chooseColor();
    if(color == 0xff0000) throw(RedException, "I don't like it.");
    if(color == 0x00ff00) throw(GreenException, NULL);
    if(color == 0x0000ff) throw(BlueException, "It's way too blue.");
    doSomething(color);
}catch(GreenException){
    printf("You cannot use green.");
}catch(ColorException){
    const e4c_exception * exception = e4c_get_exception();
    printf("You cannot use that color: %s (%s).", exception->name, exception->message);
}
```

When looking for a match, `catch` blocks are inspected in the order they appear _in the code_. If you place a handler for a superclass before a subclass handler, the second block will in fact be **unreachable**.

# Dispose Pattern #

There are other keywords related to resource handling:
  * **`with... use`**
  * **`using`**

They allow you to express the _Dispose Pattern_ in your code:

```
/* syntax #1 */
FOO foo;
with(foo, e4c_dispose_FOO) foo = e4c_acquire_FOO(bar, foobar); use do_something(foo);

/* syntax #2 (relies on 'e4c_acquire_BAR' and 'e4c_dispose_BAR') */
BAR bar;
using(BAR, bar, ("BAR", 123) ){
    do_something_else(bar);
}

/* syntax #3 (customized to specific resource types) */
FILE * report;
e4c_using_file(report, "log.txt", "a"){
    fputs("hello, world!\n", report);
}
```

This is a clean and terse way to handle all kinds of resources with implicit acquisition and automatic disposal.

# Signal Handling #

In addition, signals such as `SIGHUP`, `SIGFPE` and `SIGSEGV` can be handled in an _exceptional_ way. Forget about scary segmentation faults, all you need is to catch `BadPointerException`:

```
int * pointer = NULL;

try{
    int oops = *pointer;
}catch(BadPointerException){
    printf("No problem ;-)");
}
```

# Multithreading #

If you are using threads in your program, you must enable the _thread-safe_ version of the library by defining `E4C_THREADSAFE` at compiler level.

The usage of the framework does not vary between single and multithreaded programs. The same semantics apply. The only caveat is that **the behavior of signal handling is undefined in a multithreaded program** so use this feature with caution.

# Integration #

Whether you are developing a standalone application, or an external library that provides services to independent programs, you can integrate `exceptions4c` in your code very easily.

The system provides a mechanism for implicit initialization and finalization of the exception framework, so that it is safe to use `try`, `catch`, `throw`, etc. from any external function, even if its caller is not exception-aware whatsoever.

# Portability #

This library should compile in any ANSI C compiler. It uses nothing but standard C functions. In order to use exceptions4c you have to drop the two files (`e4c.h` and `e4c.c`) in your project and remember to `#include` the header file from your code.

In case your application uses threads, `exceptions4c` relies on pthreads, the **POSIX** application programming interface for writing multithreaded applications. This _API_ is available for most operating systems and platforms.

# Lightweight Version #

If you have the feeling that the standard version of **exceptions4c** may be _a bit overkill_ for your specific needs, there exists a **[lightweight version](lite.md)**, targeted at small projects and embedded systems. Use it when you just want to handle error conditions that may occur in your program through a simple yet powerful exception handling mechanism. It provides the **core functionality** of **exceptions4c** in **less than 200 source lines of code**.

# License #

This is **free software**: you can redistribute it and/or modify it under the terms of the **GNU Lesser General Public License** as published by the _Free Software Foundation_, either version 3 of the License, or (at your option) any later version.

This software is distributed in the hope that it will be useful, but **WITHOUT ANY WARRANTY**; without even the implied warranty of **MERCHANTABILITY** or **FITNESS FOR A PARTICULAR PURPOSE**. See the [GNU Lesser General Public License](http://www.gnu.org/licenses/lgpl.html) for more details.

You should have received a copy of the GNU Lesser General Public License along with this software. If not, see http://www.gnu.org/licenses/.

## Required ##

  * **License and copyright notice**: Include a copy of the license and copyright notice with the code.
  * **Library usage**: The library may be used within a non-open-source application.
  * **Disclose Source**: Source code for this library must be made available when distributing the software.

## Permitted ##

  * **Commercial Use**: This software and derivatives may be used for commercial purposes.
  * **Modification**: This software may be modified.
  * **Distribution**: You may distribute this software.
  * **Sublicensing**: You may grant a sublicense to modify and distribute this software to third parties not included in the license.
  * **Patent Grant**: This license provides an express grant of patent rights from the contributor to the recipient.

## Forbidden ##

  * **Hold Liable**: Software is provided without warranty and the software author/license owner cannot be held liable for damages.


---

**Share it:**
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/reddit.png)](http://www.reddit.com/r/programming/submit?url=http://code.google.com/p/exceptions4c/&title=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/digg.png)](http://digg.com/submit/?url=http://code.google.com/p/exceptions4c/&title=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/meneame.png)](http://www.meneame.net/submit.php?url=http://code.google.com/p/exceptions4c/)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/delicious.png)](http://delicious.com/save?url=http://code.google.com/p/exceptions4c/&title=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C&notes=programming)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/slashdot.png)](http://slashdot.org/bookmark.pl?url=http://code.google.com/p/exceptions4c/&title=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/barrapunto.png)](http://barrapunto.com/submit.pl?primaryskid=18&tid=83&subj=exceptions4c,%20una%20biblioteca%20para%20manejar%20excepciones%20en%20C&story=<a%20href="http://code.google.com/p/exceptions4c/">exceptions4c</a>%20es%20una%20biblioteca%20para%20manejar%20excepciones%20en%20C.)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/twitter.png)](http://twitter.com/share?text=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/g_buzz.png)](http://www.google.com/buzz/post?url=http://code.google.com/p/exceptions4c/&title=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/g_reader.png)](http://www.google.com/reader/link?url=http://code.google.com/p/exceptions4c/&srcURL=http://code.google.com/p/exceptions4c/&title=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/g_bookmarks.png)](http://www.google.com/bookmarks/mark?op=edit&output=popup&labels=c,%20exceptions,%20framework,%20try,%20catch,%20finally,%20throw,%20exception,%20error,%20handling,%20errors,%20library&bkmk=http://code.google.com/p/exceptions4c/&title=An%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/facebook.png)](http://www.facebook.com/sharer.php?src=sp&u=http://code.google.com/p/exceptions4c/&t=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/blogger.png)](http://www.blogger.com/blog_this.pyra?t=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C.&u=http://code.google.com/p/exceptions4c/&n=exceptions4c&pli=1&pli=1)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/linkdin.png)](http://www.linkedin.com/shareArticle?mini=true&ro=true&url=http://code.google.com/p/exceptions4c/&title=exceptions4c%20is%20an%20exception%20handling%20framework%20for%20C)
[![](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/16x16/email.png)](mailto:SOMEONE@SOMEWHERE.COM?subject=exceptions4c&body=http://code.google.com/p/exceptions4c/%0Aexceptions4c%20is%20an%20exception%20handling%20framework%20for%20C.)

<a href='https://plus.google.com/110309863347118550501'>Google+</a>

---


<table width='100%'>
<tr>
<td width='33%' align='left'>
<a href='http://www.gnu.org/licenses/gpl.html'>
<img src='http://exceptions4c.googlecode.com/svn/trunk/etc/img/lgpl.png' alt='GNU General Public License' width='160' height='64' />
</a>
</td>
<td width='34%' align='center'>
<wiki:gadget url="http://www.ohloh.net/p/exceptions4c/widgets/project_factoids.xml" width="400" height="170" border="0" /><br>
<a href='Hidden comment: 
Do you feel like helping out?
<br/>
<a href="https://www.paypal.com/es/cgi-bin/webscr?cmd=_flow&SESSION=WAh8UHP6aukamEmlKkyVNALp4glIWpO1Njb0yzfia0d6r0BCnmHAop9Ym94&dispatch=5885d80a13c0db1f22d2300ef60a67593b79a4d03747447e1e8d0f800ad65e80">http://exceptions4c.googlecode.com/svn/trunk/etc/img/donate_e4c.png

Unknown end tag for </a>


<br/>
Thank you for your support!
'></a><br>
</td>
<td width='33%' align='right'>
<img src='http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/sheep_064.png' />
</td>
</tr>
</table>