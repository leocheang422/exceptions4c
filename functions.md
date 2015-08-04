# `exceptions4c` Functions #

![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/exception_handling.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/exception_handling.png) **Exception context handling functions**:

  * **[e4c\_context\_is\_ready](#e4c_context_is_ready.md)** checks if the current exception context is ready.
  * **[e4c\_context\_begin](#e4c_context_begin.md)** begins an exception context.
  * **[e4c\_context\_end](#e4c_context_end.md)** ends the current exception context.
  * **[e4c\_context\_set\_signal\_mappings](#e4c_context_set_signal_mappings.md)** assigns the specified signal mappings to the exception context.
  * **[e4c\_context\_get\_signal\_mappings](#e4c_context_get_signal_mappings.md)** retrieves the signal mappings for the current exception context.
  * **[e4c\_get\_status](#e4c_get_status.md)** returns the completeness status of the executing code block.
  * **[e4c\_get\_exception](#e4c_get_exception.md)** returns the exception that was thrown.

![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/beautifully_crafted.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/24x24/beautifully_crafted.png) **Other integration and convenience functions**:

  * **[e4c\_library\_version](#e4c_library_version.md)** gets the library version number.
  * **[e4c\_is\_instance\_of](#e4c_is_instance_of.md)** returns whether an exception instance is of a given type.
  * **[e4c\_print\_exception](#e4c_print_exception.md)** prints a fatal error message regarding the specified exception.
  * **[e4c\_print\_exception\_type](#e4c_print_exception_type.md)** prints an ASCII graph representing an exception type's hierarchy.


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_context_is_ready` #

Checks if the current exception context is ready.

## Returns ##

  * Whether the current exception context of the program (or current thread) is ready to be used.

## Detailed Description ##

This function returns whether there is an actual exception context ready to be used by the program or current thread.

## See Also ##

  * **[e4c\_context\_begin](#e4c_context_begin.md)**
  * **[e4c\_context\_end](#e4c_context_end.md)**
  * **[e4c\_using\_context](macros#e4c_using_context.md)**
  * **[e4c\_reusing\_context](macros#e4c_reusing_context.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_context_begin` #

Begins an exception context.

## Parameters ##

  * **`handle_signals`**: if `E4C_TRUE`, the signal handling system will be set up with the default mapping.

## Detailed Description ##

This function begins the current exception context to be used by the program (or current thread), until [e4c\_context\_end](#e4c_context_end.md) is called.

Calling `e4c_context_begin` **twice** is considered a programming error, and therefore the program (or thread) will exit abruptly. Nevertheless, `e4c_context_begin` can be called several times _if, and only if,_ `e4c_context_end` is called in between.

The signal handling system can be automatically initialized with the default signal mapping via `handle_signals` parameter when calling `e4c_context_begin`. This is equivalent to:

```
e4c_context_set_signal_mappings(e4c_default_signal_mappings);
```

**Warning**: Note that, on some specific platforms, the behavior of the standard `signal` function might be undefined for a multithreaded program, so use the signal handling system with caution.

The convenience function [e4c\_print\_exception](functions#e4c_print_exception.md) will be used as the default [uncaught handler](types#e4c_uncaught_handler.md). It will be called in the event of an uncaught exception, before exiting the program or thread. This handler can be set through the function [e4c\_context\_set\_handlers](functions#e4c_context_set_handlers.md).

## See Also ##

  * **[e4c\_context\_end](#e4c_context_end.md)**
  * **[e4c\_context\_is\_ready](#e4c_context_is_ready.md)**
  * **[e4c\_using\_context](macros#e4c_using_context.md)**
  * **[e4c\_reusing\_context](macros#e4c_reusing_context.md)**
  * **[e4c\_uncaught\_handler](types#e4c_uncaught_handler.md)**
  * **[e4c\_print\_exception](#e4c_print_exception.md)**
  * **[e4c\_context\_set\_handlers](#e4c_context_set_handlers.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_context_end` #

Ends the current exception context.

## Detailed Description ##

This function ends the current exception context.

## Preconditions ##

  * A program (or thread) **must** begin an exception context prior to calling `e4c_context_end`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also ##

  * **[e4c\_context\_begin](#e4c_context_begin.md)**
  * **[e4c\_context\_is\_ready](#e4c_context_is_ready.md)**
  * **[e4c\_using\_context](macros#e4c_using_context.md)**
  * **[e4c\_reusing\_context](macros#e4c_reusing_context.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_context_set_signal_mappings` #

Assigns the specified signal mappings to the exception context.

## Parameters ##

  * **`mappings`**: the array of mappings.

## Detailed Description ##

This function assigns an array of mappings between the signals to be handled and the corresponding exception to be thrown.

**Warning**: Note that, on some specific platforms, the behavior of the standard `signal` function might be undefined for a multithreaded program, so use the signal handling system with caution.

## Preconditions ##

  * A program (or thread) **must** begin an exception context prior to calling `e4c_context_set_signal_mappings`. Such programming error will lead to an abrupt exit of the program (or thread).
  * `mappings` **must** be terminated by [E4C\_NULL\_SIGNAL\_MAPPING](macros#E4C_NULL_SIGNAL_MAPPING.md).

## See Also ##

  * **[e4c\_context\_get\_signal\_mappings](#e4c_context_get_signal_mappings.md)**
  * **[e4c\_signal\_mapping](types#e4c_signal_mapping.md)**
  * **[e4c\_default\_signal\_mappings](variables#e4c_default_signal_mappings.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_context_get_signal_mappings` #

Retrieves the signal mappings for the current exception context.

## Returns ##

  * The current array of mappings.

## Detailed Description ##

This function retrieves the current array of mappings between the signals to be handled and the corresponding exception to be thrown.

## Preconditions ##

  * A program (or thread) **must** begin an exception context prior to calling `e4c_context_get_signal_mappings`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also ##

  * **[e4c\_context\_set\_signal\_mappings](#e4c_context_set_signal_mappings.md)**
  * **[e4c\_signal\_mapping](types#e4c_signal_mapping.md)**
  * **[e4c\_default\_signal\_mappings](variables#e4c_default_signal_mappings.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_get_status` #

Returns the completeness status of the executing code block.

## Returns ##

  * The completeness status of the executing code block.

## Detailed Description ##

_Exception-aware_ code blocks have a completeness status regarding the exception handling system. This status determines whether an exception was actually thrown or not, and whether the exception was caught or not.

The status of the current block can be obtained any time, provided that the exception context has begun at the time of the function call. However, it is sensible to call this function only during the execution of `finally` blocks.

## Preconditions ##

  * A program (or thread) **must** begin an exception context prior to calling `e4c_get_status`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also ##

  * **[e4c\_get\_status](#e4c_get_status.md)**
  * **[finally](keywords#finally.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_get_exception` #

Returns the exception that was thrown.

## Returns ##

  * The exception that was thrown in the current exception context (if any) otherwise `NULL`.

## Detailed Description ##

This function returns a pointer to the exception that was thrown in the surrounding _exception-aware_ block, if any; otherwise `NULL`.

The function [e4c\_is\_instance\_of](#e4c_is_instance_of.md) will determine if the thrown exception is an instance of any of the defined exception types. The type of the thrown exception can also be compared for an exact type match.

```
try{
    ...
}catch(RuntimeException){
    const e4c_exception * exception = e4c_get_exception();
    if( e4c_is_instance_of(exception, SignalException.type) ){
        ...
    }else if(exception->type == NotEnoughMemoryException.type){
        ...
    }
}
```

The thrown exception can be obtained any time, provided that the exception context has begun at the time of the function call. However, it is sensible to call this function only during the execution of `finally` or `catch` blocks.

Moreover, a pointer to the thrown exception obtained _inside_ a `finally` or `catch` block **must not be used from the _outside_**.

The exception system objects are dinamically allocated and deallocated, as the program enters or exits `try`/`catch`/`finally` blocks. While it is legal to **copy** the thrown exception and access its `name` and `message` outside these blocks, care must be taken in order not to dereference the `cause` of the exception, unless it is a **deep copy** (as opposed to a **shallow copy**).

## Preconditions ##

  * A program (or thread) **must** begin an exception context prior to calling `e4c_get_exception`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also ##

  * **[e4c\_exception](types#e4c_exception.md)**
  * **[e4c\_is\_instance\_of](#e4c_is_instance_of.md)**
  * **[throw](keywords#throw.md)**
  * **[catch](keywords#catch.md)**
  * **[finally](keywords#finally.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_library_version` #

Gets the library version number.

## Returns ##

  * The version number associated with the library.

## Detailed Description ##

This function provides the same information as the `E4C_VERSION_NUMBER` macro, but the returned version number is associated with the actual, compiled library.

**Note**: This version number can be considered as the _run-time_ library version number, as opposed to the _compile-time_ library version number (specified by the header file).

**Remarks**: The library must be compiled with the corresponding header (i.e. library version number should be equal to header version number).

## See Also ##

  * **[E4C\_VERSION\_NUMBER](macros#E4C_VERSION_NUMBER.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_is_instance_of` #

Returns whether an exception instance is of a given type.

## Parameters ##

  * **`instance`**: the thrown exception.
  * **`exception_type`**: a previously defined type of exceptions.

## Returns ##

  * Whether the specified exception is an instance of the given type.

## Detailed Description ##

`e4c_is_instance_of` can be used to determine if a thrown exception **is an instance of a given type** defined through `E4C_DEFINE_EXCEPTION` and/or declared through `E4C_DECLARE_EXCEPTION`.

This macro is intended to be used in a `catch` block, or in a `finally` block provided that some exception was actually thrown (i.e. [e4c\_get\_status](#e4c_get_status.md) returned `e4c_failed` or `e4c_recovered`).

```
try{
    ...
}catch(RuntimeException){
    const e4c_exception * exception = e4c_get_exception();
    if( e4c_is_instance_of(exception, SignalException.type) ){
        ...
    }else if(exception->type == NotEnoughMemoryException.type){
        ...
    }
}
```

## Preconditions ##

  * `instance` cannot be `NULL`.
  * `type` cannot be `NULL`.

## Throws ##

  * **NullPointerException**: if either `instance` or `type` is `NULL`.

## See Also ##

  * **[e4c\_exception](types#e4c_exception.md)**
  * **[e4c\_exception\_type](types#e4c_exception_type.md)**
  * **[e4c\_get\_exception](#e4c_get_exception.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_print_exception` #

Prints a fatal error message regarding the specified exception.

## Parameters ##

  * **`exception`**: the uncaught exception.

## Detailed Description ##

This is a convenience function for showing an error message through the standard error output. It can be passed to [e4c\_context\_set\_handlers](functions#e4c_context_set_handlers.md) as the handler for uncaught exceptions, and will be used, by default, unless otherwise set up.

In absence of `NDEBUG`, this function prints as much information regarding the exception as it is available, whereas in presence of `NDEBUG`, only the `name` and `message` of the exception are printed.

## Preconditions ##

  * `exception` cannot be `NULL`.

## Throws ##

  * **NullPointerException**: if `exception` is `NULL`.

## See Also ##

  * **[e4c\_uncaught\_handler](types#e4c_uncaught_handler.md)**
  * **[e4c\_context\_begin](#e4c_context_begin.md)**
  * **[e4c\_using\_context](macros#e4c_using_context.md)**


---


# ![http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/function.png) `e4c_print_exception_type` #

Prints an ASCII graph representing an exception type's hierarchy.

## Parameters ##

  * **`exception_type`**: an exception type.

## Detailed Description ##

This is a convenience function for showing an ASCII graph representing an exception type's hierarchy through the standard error output.

For example, the output for `ProgramSignal2Exception` would be:

```
Exception hierarchy
________________________________________________________________

    RuntimeException
     |
     +--SignalException
         |
         +--ProgramSignalException
             |
             +--ProgramSignal2Exception
________________________________________________________________
```

## Preconditions ##

  * `exception_type` cannot be `NULL`.

## Throws ##

  * **NullPointerException**: if `exception_type` is `NULL`.

## See Also ##

  * **[e4c\_exception\_type](types#e4c_exception_type.md)**


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)