# Multithreading #

If you are using threads in your program, you must enable the _thread-safe_ version of the library by defining `E4C_THREADSAFE` at compiler level.

The usage of the framework does not vary between single and multithreaded programs. The same semantics apply. The only caveat is that **the behavior of signal handling is undefined in a multithreaded program** so use this feature with caution.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)