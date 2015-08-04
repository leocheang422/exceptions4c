# A Little `Context` #

The exception-aware code of the program needs to be enclosed in a **context**. A context needs to be _begun_ before using the exception handling and _ended_ before exiting the application or thread.

The easiest way to do this is through the macro `e4c_using_context`. Everything inside this code block (or called from this code block) has an exception context ready to be used. For example, you can place it in your `main` function and you are done:

```
int main(int argc, char * argv[]){
    e4c_using_context(E4C_TRUE){
        ...
    }
}
```

There is another way to begin and end an exception context through the functions `e4c_context_begin` and `e4c_context_end`, but you will need to use them _properly_ (you cannot call twice in a row any of these functions, and you need to end the context before exiting).

# Exception Types #

The types of exceptions a program will use are defined within the global scope of a source code file through the macro `E4C_DEFINE_EXCEPTION` specifying: **name**, **default error message** and **supertype**:

```
/* stack.c */
...
E4C_DEFINE_EXCEPTION(StackException, "Stack overflow", RuntimeException);
E4C_DEFINE_EXCEPTION(StackOverflowException, "Stack overflow", StackException);
E4C_DEFINE_EXCEPTION(StackUnderflowException, "Stack underflow", StackException);
...
```

They can be declared in a header file through the macro `E4C_DECLARE_EXCEPTION`:

```
/* stack.h */
...
E4C_DECLARE_EXCEPTION(StackException);
E4C_DECLARE_EXCEPTION(StackOverflowException);
E4C_DECLARE_EXCEPTION(StackUnderflowException);
...
```

# `throw` #

The _keyword_ `throw` creates a new instance of the specified exception type, with the specified mesage and raises it to signal an exceptional situation to the system.

If the specified message is `NULL` then the default message for that type of exception will be used.

```
if(record == null) throw(NullPointerException, "Invalid record passed as parameter.");

buffer = malloc(1024);

if(buffer != null){
	...
}else{
	throw(NotEnoughMemoryException, NULL);
}
```

Exceptions can be thrown any time, provided that there is an exception context ready to be used. They can be thrown even from `catch` and `finally` blocks.

# `try` #

The only mandatory part of a `try` block is the `try` _keyword_. A code block introduced by the `try` keyword can use `catch` blocks in order to handle errors, and a `finally` block to cleanup after the `try` block either _succeeds_ or _fails_.

```
try{
    stack_push(123);
}
```

# `catch` #

A `catch` block must be given a type of exceptions it is capable of handling. Inside a `catch` block, the actual exception being handled can be accessed through the function `e4c_get_exception`.

```
try{
    stack_push(123);
}catch(StackException){
    printf("Last operation failed (%s).\n", e4c_get_exception()->message);
}
```

A `try` block can be followed by many `catch` blocks:

```
try{
    stack_push(stack, 123);
    foo = stack_pop(stack);
}catch(StackOverflowException){
    /* ... */
}catch(StackUnderflowException){
    /* ... */
}
```

# `finally` #

A `try` block can be followed by, at most, one `finally` block. In order to know whether the `try` block completed or threw an exception, you can call the function `e4c_get_status`. The function `e4c_get_exception` will return the thrown exception, if any, even if it was caught by a `catch` block.

```
try{
    stack_push(123);
}finally{
    fclose(file);
    switch( e4c_get_status() ){
        case e4c_succeeded:
            ...
            break;
        case e4c_recovered:
            ...
            break;
        case e4c_failed:
            ...
            break;
    }
}
```


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)