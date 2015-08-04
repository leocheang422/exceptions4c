# `exceptions4c` Macros #

![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/exception_handling.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/exception_handling.png) **Exception handling macros**:

  * **[E4C\_DECLARE\_EXCEPTION](#E4C_DECLARE_EXCEPTION.md)** declares an exception type.
  * **[E4C\_DEFINE\_EXCEPTION](#E4C_DEFINE_EXCEPTION.md)** defines an exception type.
  * **[e4c\_using\_context](#e4c_using_context.md)** introduces a block of code which will use a new exception context.
  * **[e4c\_reusing\_context](#e4c_reusing_context.md)** reuses an existing exception context, otherwise, begins a new one and then ends it.

![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/signal_handling.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/signal_handling.png) **Signal handling macros**:

  * **[E4C\_SIGNAL\_MAPPING](#E4C_SIGNAL_MAPPING.md)** maps a specific signal number to a given exception type.
  * **[E4C\_IGNORE\_SIGNAL](#E4C_IGNORE_SIGNAL.md)** ignores a specific signal number.
  * **[E4C\_NULL\_SIGNAL\_MAPPING](#E4C_NULL_SIGNAL_MAPPING.md)** represents a null signal mapping literal.

![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/portable.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/portable.png) **Integration macros**:

  * **[E4C\_VERSION\_NUMBER](#E4C_VERSION_NUMBER.md)** provides the library version number.
  * **[E4C\_VERSION\_THREADSAFE](#E4C_VERSION_THREADSAFE.md)** provides the library thread mode (either single-thread or multi-thread)
  * **[E4C\_VERSION\_MAJOR](#E4C_VERSION_MAJOR.md)** provides the library major version number.
  * **[E4C\_VERSION\_MINOR](#E4C_VERSION_MINOR.md)** provides the library minor version number.
  * **[E4C\_VERSION\_REVISION](#E4C_VERSION_REVISION.md)** provides the library revision number.
  * **[E4C\_VERSION\_STRING](#E4C_VERSION_STRING.md)** provides the library version number as a string literal.
  * **[E4C\_EXCEPTION\_MESSAGE\_SIZE](#E4C_EXCEPTION_MESSAGE_SIZE.md)** provides the maximum length (in bytes) of an exception message.
  * **[E4C\_ON\_FAILURE](#E4C_ON_FAILURE.md)** provides a means of parsing an exception to obtain a status value.
  * **[E4C\_NORETURN](#E4C_NORETURN.md)** marks a function which never returns.
  * **[E4C\_UNREACHABLE\_RETURN](#E4C_UNREACHABLE_RETURN.md)** simulates a function return.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_DECLARE_EXCEPTION` #

Declares an exception type.

## Parameters ##

  * **`name`**: name of the exception type.

## Detailed Description ##

This macro introduces the name of an `extern`, `const` exception which will be available to be thrown or caught:

```
E4C_DECLARE_EXCEPTION(StackException);
E4C_DECLARE_EXCEPTION(StackOverflowException);
E4C_DECLARE_EXCEPTION(StackUnderflowException);
```

This macro is intended to be used inside header files.

**Note**: when you _declare_ exception types, no storage is allocated. In order to actually _define_ them, you need to use the macro [E4C\_DEFINE\_EXCEPTION](#E4C_DEFINE_EXCEPTION.md).

## See Also ##

  * **[e4c\_exception\_type](types#e4c_exception_type.md)**
  * **[E4C\_DEFINE\_EXCEPTION](#E4C_DEFINE_EXCEPTION.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_DEFINE_EXCEPTION` #

Defines an exception type.

## Parameters ##

  * **`name`**: name of the new exception type.
  * **`message`**: default message of the new exception type.
  * **`super`**: supertype of the new exception type.

## Detailed Description ##

This macro allocates a new, `const` exception type.

```
E4C_DEFINE_EXCEPTION(StackException, "Stack exception", RuntimeException);
E4C_DEFINE_EXCEPTION(StackOverflowException, "Stack overflow", StackException);
E4C_DEFINE_EXCEPTION(StackUnderflowException, "Stack underflow", StackException);
```

This macro is intended to be used inside sorce code files. The defined exception types can be declared in a header file through the macro [E4C\_DECLARE\_EXCEPTION](#E4C_DECLARE_EXCEPTION.md).

## See Also ##

  * **[e4c\_exception\_type](types#e4c_exception_type.md)**
  * **[RuntimeException](variables#RuntimeException.md)**
  * **[E4C\_DECLARE\_EXCEPTION](#E4C_DECLARE_EXCEPTION.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `e4c_using_context` #

Introduces a block of code which will use a new exception context.

## Parameters ##

  * **`handle_signals`**: if `E4C_TRUE`, the signal handling system will be set up with the default mapping.

## Detailed Description ##

This macro begins a new exception context to be used by the code block right next to it. When the code completes, `e4c_context_end` will be called implicitly.

This macro is very convenient when the beginning and the ending of the current exception context are next to each other. For example, there is no semantic difference between this two blocks of code:

```
// block 1
e4c_context_begin(E4C_TRUE);
// ...
e4c_context_end();

// block 2
e4c_using_context(E4C_TRUE){
    // ...
}
```

This macro **always** attempts to begin a new exception context, whereas `e4c_reusing_context` only does if there is no exception context, already begun, to be used.

This macro **should be used whenever possible**, rather than doing the explicit, manual calls to `e4c_context_begin` and
`e4c_context_end`, because it is less prone to errors.

**Warning**: a block introduced by `e4c_using_context` **must not** be _broken_, through `goto`, `return` nor `break`.

## See Also ##

  * **[e4c\_context\_begin](functions#e4c_context_begin.md)**
  * **[e4c\_context\_end](functions#e4c_context_end.md)**
  * **[e4c\_reusing\_context](#e4c_reusing_context.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `e4c_reusing_context` #

Reuses an existing exception context, otherwise, begins a new one and then ends it.

## Parameters ##

  * **`status`**: the name of a previously defined variable, or lvalue, which will be assigned the specified failure value.
  * **`on_failure`**: a constant value or expression that will be assigned to the specified lvalue in case of failure.

## Detailed Description ##

This macro lets library developers use the exception framework, regardless of whether the library clients are unaware of the exception handling system. In a nutshell, function libraries can use `try`, `catch`, `throw`, etc. whether the client previously began an exception context or not.

You **must not use this macro** unless you are implementing some functionality which is to be called from another program, potentially unaware of exceptions.

A block introduced by `e4c_reusing_context` is guaranteed to take place _inside_ an exception context. When the block completes, the system returns to its previous status (if it was required to open a new exception context, then it will be automatically closed).

This way, when an external functions encounters an error, it may either throw an exception (when the caller is aware of the exception system), or otherwise return an error code (when the caller did not open an exception context).

`e4c_reusing_context` needs to be given a `status` variable (or _lvalue_) that will be assigned a specified failure value when an exception is thrown inside the block. The failure _rvalue_ can be any expression assignable to the specified status _lvalue_.

```
int library_public_function(void * pointer, int number){

    // We don't know where this function is going to be called from, so:
    //   * We cannot use "try", "throw", etc. right here, because the
    //   exception context COULD be uninitialized at this very moment.
    //   * We cannot call "e4c_context_begin" either, because the
    //   exception context COULD be already initialized.
    // If we have to make use of the exception handling system, we need to
    // "reuse" the existing exception context or "use" a new one.

    volatile int status = STATUS_OK;

    e4c_reusing_context(status, STATUS_ERROR){

        // Now we can safely use "try", "throw", etc.
        if(pointer == NULL){
            throw(NullPointerException);
        }

        library_private_function(pointer, number);
    }

    return(status);
}
```

The status will be left unmodified if the client (i.e. the function caller) is _exception-aware_, or the block _completes_ without an error (i.e. no exception is thrown), so it **must** be properly initialized before returning it.

Please note that the status needs not be just a dichotomy (success or failure). It can be a fine-grained value describing what exactly went wrong. You can pass any expression to `e4c_reusing_context` wich will be evaluated if an exception is thrown:

```
int library_public_function(void * pointer, int number){

    volatile int status = STATUS_OK;
    volatile bool flag = true;

    e4c_reusing_context(status, (flag ? STATUS_NULL_POINTER : STATUS_ERROR)){

        if(pointer == NULL){
            throw(NullPointerException);
        }

        flag = false;

        library_private_function(pointer, number);
    }

    return(status);
}
```

However, Most of the times you probably want to yield a different status value depending on the specific exception being thrown. This can be easily accomplished by making use of the macro `E4C_ON_FAILURE`.

Next, the semantics of `e4c_reusing_context` are explained, step by step:

  * If there is an exception context at the time the block starts:
    1. The existing exception context will be reused.
    1. The code block will take place.
    1. If any exception is thrown during the execution of the block:
      * It will be **propagated** upwards to the caller.
      * The control will be transferred to the nearest surrounding block of code which is able to handle that exception.
  * If there is no exception context at the time the block starts:
    1. A new exception context will be begun; note that the signal handling system **will NOT** be set up.
    1. The code block will take place.
    1. If any exception is thrown during the execution of the block:
      * It will be **caught**.
      * `status` will be asigned the value of the expression `on_failure`.

If you need to perform any cleanup, you should place it _inside_ a `finally` block, for example:

```
...
e4c_reusing_context(status, STATUS_ERROR){

    void * buffer = NULL;
    try{
        buffer = malloc(1024);
        ...
    }finally{
        free(buffer);
    }
}
...
```

If you need to rely on the signal handling system, you may call `e4c_context_set_signal_mappings` explicitly. You must take into account that you could be _hijacking_ your client's original signal mappings, so you should also call `e4c_context_get_signal_mappings` in order to restore the previous signal mappings when you are done.

```
const e4c_signal_mapping new_mappings[] = {
    E4C_SIGNAL_MAPPING(SIGABRT, Exception1),
    E4C_SIGNAL_MAPPING(SIGINT, Exception2),
    E4C_IGNORE_SIGNAL(SIGTERM),
    ...
    E4C_NULL_SIGNAL_MAPPING
};
...
e4c_reusing_context(status, STATUS_ERROR){

    const e4c_signal_mapping * old_mappings = e4c_context_get_signal_mappings();

    e4c_context_set_signal_mappings(new_mappings);

    try{
        ...
    }finally{
        e4c_context_set_signal_mappings(old_mappings);
    }
}
...
```

This macro only begins a new exception context **if there is no one, already begun, to be used** whereas `e4c_using_context` always attempts to begin a new one.

**Warning**: a block introduced by `e4c_reusing_context` **must not** be _broken_, through `goto`, `return` nor `break`.

## See Also ##

  * **[e4c\_context\_begin](functions#e4c_context_begin.md)**
  * **[e4c\_context\_end](functions#e4c_context_end.md)**
  * **[e4c\_context\_is\_ready](functions#e4c_context_is_ready.md)**
  * **[e4c\_using\_context](#e4c_using_context.md)**
  * **[e4c\_exception](types#e4c_exception.md)**
  * **[E4C\_ON\_FAILURE](#E4C_ON_FAILURE.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_SIGNAL_MAPPING` #

Maps a specific signal number to a given exception type.

## Parameters ##

  * **`signal_number`**: numeric value of the signal to be converted.
  * **`exception_type`**: exception type representing the signal.

## Detailed Description ##

This macro represents a signal mapping literal. It comes in handy for initializing arrays of `e4c_signal_mapping`.

## See Also ##

  * **[e4c\_signal\_mapping](types#e4c_signal_mapping.md)**
  * **[e4c\_context\_set\_signal\_mappings](functions#e4c_context_set_signal_mappings.md)**
  * **[e4c\_context\_get\_signal\_mappings](functions#e4c_context_get_signal_mappings.md)**
  * **[E4C\_IGNORE\_SIGNAL](#E4C_IGNORE_SIGNAL.md)**
  * **[E4C\_NULL\_SIGNAL\_MAPPING](#E4C_NULL_SIGNAL_MAPPING.md)**
  * **[E4C\_DECLARE\_EXCEPTION](#E4C_DECLARE_EXCEPTION.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_IGNORE_SIGNAL` #

Ignores a specific signal number.

## Parameters ##

  * **`signal_number`**: numeric value of the signal to be ignored.

## Detailed Description ##

This macro represents a signal mapping literal. It comes in handy for initializing arrays of `e4c_signal_mapping`.

## See Also ##

  * **[e4c\_signal\_mapping](types#e4c_signal_mapping.md)**
  * **[e4c\_context\_set\_signal\_mappings](functions#e4c_context_set_signal_mappings.md)**
  * **[e4c\_context\_get\_signal\_mappings](functions#e4c_context_get_signal_mappings.md)**
  * **[E4C\_SIGNAL\_MAPPING](#E4C_SIGNAL_MAPPING.md)**
  * **[E4C\_NULL\_SIGNAL\_MAPPING](#E4C_NULL_SIGNAL_MAPPING.md)**
  * **[E4C\_DECLARE\_EXCEPTION](#E4C_DECLARE_EXCEPTION.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_NULL_SIGNAL_MAPPING` #

Represents a null signal mapping literal.

## Detailed Description ##

This macro comes in handy for terminating arrays of `e4c_signal_mapping`.

## See Also ##

  * **[e4c\_signal\_mapping](types#e4c_signal_mapping.md)**
  * **[e4c\_context\_set\_signal\_mappings](functions#e4c_context_set_signal_mappings.md)**
  * **[e4c\_context\_get\_signal\_mappings](functions#e4c_context_get_signal_mappings.md)**
  * **[E4C\_SIGNAL\_MAPPING](#E4C_SIGNAL_MAPPING.md)**
  * **[E4C\_IGNORE\_SIGNAL](#E4C_IGNORE_SIGNAL.md)**
  * **[E4C\_DECLARE\_EXCEPTION](#E4C_DECLARE_EXCEPTION.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_VERSION_NUMBER` #

Provides the library version number.

## Detailed Description ##

The library version number is a `long` value which expresses:

  * library thread mode (either _single-thread_ or _multi-thread_)
  * library _major_ version number
  * library _minor_ version number
  * library _revision_ number

The multi-thread (or _thread-safe_) mode can be obtained by compiling the library with the `E4C_THREADSAFE` _compile-time_ parameter.

The formula to encode these version numbers into a single `long` value is:

```
THREADSAFE * 10000000 + MAJOR * 1000000 + MINOR * 1000 + REVISION
```

These numbers can be obtained separately through the next macros:

  * `E4C_VERSION_THREADSAFE`
  * `E4C_VERSION_MAJOR`
  * `E4C_VERSION_MINOR`
  * `E4C_VERSION_REVISION`

The library version number can be also obtained as a string literal in the format "MAJOR.MINOR.REVISION (THREADSAFE)" through the macro `E4C_VERSION_STRING`.

This version number can be considered as the _compile-time_ library version number, as opposed to the _run-time_ library version number (associated with the actual, compiled library). This _run-time_ version number can be obtained through the function `e4c_library_version`.

The library **must** be compiled with the corresponding header (i.e. library version number should be equal to header version number).

## See Also ##

  * **[e4c\_library\_version](functions#e4c_library_version.md)**
  * **[E4C\_VERSION\_THREADSAFE](#E4C_VERSION_THREADSAFE.md)**
  * **[E4C\_VERSION\_MAJOR](#E4C_VERSION_MAJOR.md)**
  * **[E4C\_VERSION\_MINOR](#E4C_VERSION_MINOR.md)**
  * **[E4C\_VERSION\_REVISION](#E4C_VERSION_REVISION.md)**
  * **[E4C\_VERSION\_STRING](#E4C_VERSION_STRING.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_VERSION_THREADSAFE` #

Provides the library thread mode (either single-thread or multi-thread).

## Detailed Description ##

When the library is compiled with the `E4C_THREADSAFE` _compile-time_ parameter, `E4C_VERSION_THREADSAFE` will yield the `int` value `1` (meaning _multi-thread_ mode), otherwise it will yield the `int` value `0` (meaning _single-thread_ mode).

## See Also ##

  * **[E4C\_VERSION\_NUMBER](#E4C_VERSION_NUMBER.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_VERSION_MAJOR` #

Provides the library major version number.

## Detailed Description ##

The library major version number is an `int` value which is incremented from one release to another **when there are significant changes in functionality**.

## See Also ##

  * **[E4C\_VERSION\_NUMBER](#E4C_VERSION_NUMBER.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_VERSION_MINOR` #

Provides the library minor version number.

## Detailed Description ##

The library minor version number is an `int` value which is incremented from one release to another when **only minor features or significant fixes have been added**.

## See Also ##

  * **[E4C\_VERSION\_NUMBER](#E4C_VERSION_NUMBER.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_VERSION_REVISION` #

Provides the library revision number.

## Detailed Description ##

The library revision number is an `int` value which is incremented from one release to another when **minor bugs are fixed**.

## See Also ##

  * **[E4C\_VERSION\_NUMBER](#E4C_VERSION_NUMBER.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_VERSION_STRING` #

Provides the library version number as a string literal.

## Detailed Description ##

The format of the string literal is: "MAJOR.MINOR.REVISION (THREADSAFE)".

## See Also ##

  * **[E4C\_VERSION\_NUMBER](#E4C_VERSION_NUMBER.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_EXCEPTION_MESSAGE_SIZE` #

Provides the maximum length (in bytes) of an exception message.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_ON_FAILURE` #

Provides a means of parsing an exception to obtain a status value.

## Parameters ##

  * **`handler`**: The name of the parser function to be called.

## Detailed Description ##

This is a handy way to call a function when a `e4c_reusing_context` block fails. This function will be passed the current thrown exception; it is expected to parse it and return a proper status value.

```
static int parse_exception(const e4c_exception * exception){

    if(exception->type == &NotEnoughMemoryException){
        return(STATUS_MEMORY_ERROR);
    }else if( is_instance_of(exception, &MyException) ){
        return(STATUS_MY_ERROR);
    }

    return(STATUS_ERROR);
}

int library_public_function(void * pointer, int number){

    volatile int status = STATUS_OK;

    e4c_reusing_context(status, E4C_ON_FAILURE(parse_exception)){

        if(pointer == NULL){
            throw(NullPointerException);
        }

        library_private_function(pointer, number);
    }

    return(status);
}
```

## See Also ##

  * **[e4c\_reusing\_context](#e4c_reusing_context.md)**
  * **[e4c\_get\_exception](functions#e4c_get_exception.md)**
  * **[e4c\_exception](types#e4c_exception.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_NORETURN` #

Marks a function which never returns.

## Detailed Description ##

This macro helps both developer and compiler to assume that the marked function will not return the control to its caller (unless by throwing an exception).

**Note**: it does not make sense for these functions to have a return type other than `void`.

For example, a function `f1` that **always** throws an exception, could be marked with this macro:

```
void f1(int foo) E4C_NORETURN;
// ...
void f1(int foo){
    if(foo == 1){
        throw(MyException1, "foo is one.");
    }
    throw(MyException2, "foo is not one.");
}
```

Then, if another function tested a condition and then called `f1`, it wouldn't need to return anything witnin the `if` branch, nor consider the `else` branch of the test:

```
int f2(int bar, int foo){

    if(bar == 0){
        f1(foo);
        // return(-1);
    }// else

    return(123);

}
```

If the compiler supports this macro, it could optimize the program and avoid spurious warnings of uninitialized variables.

## See Also ##

  * **[E4C\_UNREACHABLE\_RETURN](#E4C_UNREACHABLE_RETURN.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/macro.png) `E4C_UNREACHABLE_RETURN` #

Simulates a function return.

## Parameters ##

  * **`value`**: the value that would be returned if the statement took place.

## Detailed Description ##

This macro ensures portability on compilers which don't support functions that never return.

**Note**: it does not make sense using this macro in `void` functions.

It **must** be used after calling a function marked as `E4C_NORETURN`, so that the compiler will not complain about _control reaching end of non-void function_. For example:

```
void f1(int foo) E4C_NORETURN;

int f3(int bar, int foo){

    if(bar != 0){
        return(123);
    }

    f1(123);

    E4C_UNREACHABLE_RETURN(-1);
}
```

This macro will become an actual `return` statement if the compiler does not support `E4C_NORETURN`, even though it will never be reached (because the called function won't actually return control).

## See Also ##

  * **[E4C\_NORETURN](#E4C_NORETURN.md)**


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)