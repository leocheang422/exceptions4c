# Integration #

Whether you are developing a standalone application, or an external library that provides services to independent programs, you can integrate `exceptions4c` in your code very easily.

The system provides a mechanism for implicit initialization and finalization of the exception framework, so that it is safe to use `try`, `catch`, `throw`, etc. from any external function, even if its caller is not exception-aware whatsoever.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)