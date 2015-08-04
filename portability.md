# Portability #

This library should compile in any good old C compiler. It uses nothing but standard C functions. In order to use exceptions4c you have to drop the two files (`e4c.h` and `e4c.c`) in your project and remember to `#include` the header file from your code.

# Keywords #

All of the names of the functions, defined types and macros start with the preffix `e4c_` in order to prevent namespace pollution. However, `exceptions4c` defines the next set of _keywords_ (through macros) for convenience:

  * `try`
  * `finally`
  * `throw`
  * `catch`
  * `with`
  * `use`
  * `using`

If, for some reason, you don't want the library to define these _keywords_, you can compile the library with the `E4C_NOKEYWORDS` _compile-time_ parameter and use their respective alternate versions:

  * `E4C_TRY`
  * `E4C_FINALLY`
  * `E4C_THROW`
  * `E4C_CATCH`
  * `E4C_WITH`
  * `E4C_USE`
  * `E4C_USING`

# C99-only Features #

There is a convenience macro that lets you to compose a formatted message and throw an exception _on the fly_.

```
int bytes = 1024;
void * buffer = malloc(bytes);
if(buffer == NULL){
    throwf(NotEnoughMemoryException, "Could not allocate %d bytes.", bytes);
}
```

This macro relies on two features that were introduced in **C99**:

  * Variadic macros
  * Buffer-safe function **`vsnprintf`**

In order not to create compatibility issues, this macro will only be defined when the `__STDC_VERSION__` _compile-time_ parameter is defined with a value _greater than or equal to_ `199901L`, or `HAVE_C99_VARIADIC_MACROS` is defined.

Of course, the alternative way to compose a message and then throw it would be to call `snprintf` (or its _unsafe_ alternative `sprintf`):

```
int bytes = 1024;
void * buffer = malloc(bytes);
if(buffer == NULL){
    char message[E4C_EXCEPTION_MESSAGE_SIZE];
    snprintf(message, E4C_EXCEPTION_MESSAGE_SIZE, "Could not allocate %d bytes.", bytes);
    throw(NotEnoughMemoryException, message);
}
```

The semantics of this macro are the same as for the `throw` macro.

At least one argument must be passed right after the format string. The message will be composed through the function `vsnprintf` with the specified format and variadic arguments. For further information on the formatting rules, you may look up the specifications for the function `vsnprintf`.

# Multi-threading #

In case your application uses threads, `exceptions4c` relies on pthreads, the **POSIX** application programming interface for writing multithreaded applications. This _API_ is available for most operating systems and platforms. You only need to compile the library with the `E4C_THREADSAFE` _compile-time_ parameter.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)