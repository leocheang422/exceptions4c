# Introduction #

A signal is an asynchronous notification sent by the operating system to a process in order to notify it of an event that occurred. Most of the signals will, by default, crash the program as soon as they are raised.

**exceptions4c** can make your life easier by converting signals to exceptions, so you can can `catch` signals and avoid core dumps.

For example, you could wrap a _suspicious_ or _dangerous_ part of the code with `try` blocks and `catch` segmentation faults or divisions by zero. Then you can clean up and keep working:

```
e4c_using_context(E4C_TRUE){
    int * pointer = NULL;
    try{
        int oops = *pointer;
    }catch(BadPointerException){
        printf("No problem ;-)");
    }finally{
        /* clean up... */
    }
}
```

# Usage #

In order to perform the conversion, **exceptions4c** maps signals to exceptions.

The simplest way to get this working is by passing `handle_signals=E4C_TRUE` to the macro `e4c_using_context` or the function `e4c_context_begin`. This will set up the default mappings for the available signals in the platform.

If you need to be more specific about which signals get converted to exceptions, you can define an array of `e4c_signal_mapping` and pass it to the function `e4c_context_set_signal_mappings`.

```
e4c_signal_mapping my_signal_mappings[] = {
    E4C_SIGNAL_MAPPING(SIGABRT, Exception1),
    E4C_SIGNAL_MAPPING(SIGINT, Exception2),
    ...
    E4C_NULL_SIGNAL_MAPPING
}
...
e4c_using_context(E4C_FALSE){
    e4c_context_set_signal_mappings(my_signal_mappings);
}
```

An array of signal mappings is defined through the macros `E4C_SIGNAL_MAPPING`, `E4C_IGNORE_SIGNAL` and `E4C_NULL_SIGNAL_MAPPING`. Every `e4c_signal_mapping` array needs to be terminated by the _null signal mapping_ element, so the system finds out how many mappings there are in a given array.

Once the array is properly defined, it can be passed to the function `e4c_context_set_signal_mappings`. This way, only the specified signals will be handled as exceptions, and they will be converted to the specified exceptions.

Additionally, you can _ignore_ specific signals by using `E4C_IGNORE_SIGNAL` instead of `E4C_SIGNAL_MAPPING`. If the specified signal is raised, the system won't convert it to an exception and the program will continue (even if unmeaningful).

If you want to disable signal handling, you can pass `NULL` to the function `e4c_context_set_signal_mappings`.

There is also a function to obtain the current signal mappings (or `NULL`, if disabled) called `e4c_context_get_signal_mappings`.

# Signals you can handle #

These are some of the signals you can handle:
  * **SIGFPE** (for example, when you try to divide by zero)
  * **SIGSEGV** (when you make an invalid memory reference, or segmentation fault)
  * **SIGINT** (when a user wishes to interrupt the process, Control-c)
  * **SIGTERM** (the signal sent to a process to request its termination)

Obviously, you should conform to the semantics of each signal. Remember to read your platform specifications.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)