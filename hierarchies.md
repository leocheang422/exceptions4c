# Exception hierarchies #

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
    e4c_exception * exception = e4c_get_exception();
    printf("You cannot use that color: %s (%s).", exception->name, exception->message);
}
```

When looking for a match, `catch` blocks are inspected in the order they appear _in the code_. If you place a handler for a superclass before a subclass handler, the second block will be rendered **unreachable**.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)