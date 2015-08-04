# Drawbacks #

  * Blocks introduced by a _keyword_ **CAN'T** be _broken_. You cannot use neither `return`, `goto`, `break` or `continue` to jump out of any `try`, `catch`, `finally`, `with` or `use` blocks. You can `throw` exceptions, though. The same apply to blocks introduced by `e4c_using_context` or `e4c_reusing_context`.
  * Exceptions are _unchecked_, so you should wrap your application's main loop with a _catch-all_ block if you don't want your application exiting when an exception pops out `main`.

# Special cases #

  * `AssertionException` cannot be caught whatsoever. In addition, if a [finally](finally.md) block attempts to [retry](retry.md) the block when an assertion exception has been previously thrown, the [retry](retry.md) will not take place.

  * Fatal errors regarding the exception handling system (such as attempting to [throw](throw.md) an exception without a proper context) cannot be handled by the program.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)