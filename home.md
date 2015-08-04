# Introduction #

The traditional way of handle errors in C is checking the value of error codes in order to find out the status of the last operation. This old technique is tedious and error-prone, because programmers don't always remember to look at error codes.

Exception handling is a programming language construct, built into many high-level languages, designed to handle the occurrence of special conditions that change the normal flow of program execution. Exceptions have the advantage of being handled with explicit blocks of code, separate from the rest of the code.

# Overview #

This library provides you a simple set of keywords (_macros_, actually):
  * **`try`**
  * **`catch`**
  * **`finally`**
  * **`throw`**

When some part of the program finds an error that can't handle, it must `throw` an exception and then the flow of the program jumps to a block of code that is able to handle the error.

In order to handle the error, the part of the code that threw the exception must have been called by a block of code marked as `try` next to a `catch` block which is able to handle the exception, or any supertype of the exception.

If a `try` block does not contain a `catch` block capable of handling the exception and there is a `finally` block, it is executed before looking for the next outter `try` block.

If no surrounding block of code is able to handle that kind of exception, the program ends _gracefully_.

# Features #

You can `throw` and `catch` exceptions imported from any other code, and you can create your own exceptions too. Moreover, exceptions can be organized into _pseudo-hierarchies_, so you can catch many specialized exceptions by catching a generic one.

A really useful feature is that `finally` blocks are **always** executed, no matter whether exceptions were thrown or not, so you can rely on them to safely dispose resources, deallocate memory and stuff like that.

There is also a _built-in_ mechanism to express the **Dispose Pattern** in your program, so the resources can be implicitly acquired, used and then disposed, saving a lot of boilerplate code.

In addition, signals such as `SIGHUP`, `SIGFPE` and `SIGSEGV` can be handled in an _exceptional_ way. These signals are sent to the process when something really bad happens, such as: division by zero, segmentation fault, etc.

# Usage #

You might want to play around with **`exceptions4c`** before actually using it in your projects, but you will realize very soon it's really easy to work with. In order to use **`exceptions4c`**, you just need to drop the two files (`e4c.h` and `e4c.c`) in your project and remember to include the header file from your code.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)