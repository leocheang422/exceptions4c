# Getting started #

This short tutorial will show you how to start using the exception handling framework in your applications. We will see how we can incorporate `exceptions4c` into a test project. Let's suppose we are developing an application component which represents a _integer stack_. We have defined a terse interface to operate on such objects.

# Our simple `stack` component #

```
/* stack.h */

typedef struct my_stack int_stack;
struct int_stack{...};

extern void stack_construct(int_stack * stack, int max_items);
extern void stack_destruct(int_stack * stack);
extern void stack_push(int_stack * stack, int item);
extern int stack_pop(int_stack * stack);
extern bool stack_is_empty(int_stack * stack);
extern bool stack_is_full(int_stack * stack);
```

# Using return codes to signal errors? #

Now let's have a look at two of those functions: `stack_push` and `stack_pop`. What happens if any of these functions fails? The typical approach would be to make them return an error code to express operation failure. But then `stack_pop` would need another argument in order to _return_ the item:

```
enum stack_status{stack_success, stack_error_full, stack_error_empty};
...
extern enum stack_status stack_push(int_stack * stack, int item);
extern enum stack_status stack_pop(int_stack * stack, int * item);
...
```

# Let's rather use exceptions to signal errors #

We believe it could be more convenient to let these function throw an exception in case of error. For example, `stack_push` could throw `StackOverflowException` when the stack is full, and `stack_pop` could throw `StackUnderflowException` when the stack is empty.

It is simple enough and yet powerful, so we don't need to spoil the API by returning status codes everywhere, or passing pointers just to get the actual result.

# Defining our exceptions #

So we need to start by defining the exception types our stack component will use. It can be handy to define a hierarchy of stack exceptions in order to be able to handle them in a generic way.

```
/* stack.c */
E4C_DEFINE_EXCEPTION(StackException, "Last stack operation failed.", RuntimeException);
E4C_DEFINE_EXCEPTION(StackOverflowException, "The stack is full.", StackException);
E4C_DEFINE_EXCEPTION(StackUnderflowException, "The stack is empty.", StackException);
...
```

# Declaring our exceptions #

Just as we _export_ our component functions and make them publicly available through a header file with their `extern` prototypes, we need to _export_ our exceptions too, so a caller finds out about them.

```
/* stack.h */
E4C_DECLARE_EXCEPTION(StackException);
E4C_DECLARE_EXCEPTION(StackOverflowException);
E4C_DECLARE_EXCEPTION(StackUnderflowException);
...
```

# Throwing exceptions #

Now we can modify the implementation of `stack_push` and `stack_pop` and make them throw an exception at stack overflow / underflow. By the way, we can also make them throw a `NullPointerException` when the argument passed is `NULL`.

```
void stack_push(int_stack * stack, int item){

    if(stack == NULL) throw(NullPointerException, "Stack argument is null.");

    if( stack_is_full(stack) ) throw(StackOverflowException, NULL);

    ...
}

int stack_pop(int_stack * stack);

    if(stack == NULL) throw(NullPointerException, "Stack argument is null.");

    if( stack_is_empty(stack) ) throw(StackUnderflowException, NULL);

    ...
}
```

# Documenting exceptions that may be thrown #

It is a good practice to document which exceptions a function can throw (and under what circumstances), so the caller can get ready to handle them.

```
/**
 * Pushes an item onto the top of the stack.
 *
 * @param stack The stack to push to
 * @param item The item to be pushed
 *
 * @throws NullPointerException if stack is NULL
 * @throws StackOverflowException if stack is full
 */
extern void stack_push(int_stack * stack, int item);


/**
 * Returns (and removes) the item at the top of the stack.
 *
 * @param stack The stack to pop from
 * @return the topmost item
 *
 * @throws NullPointerException if stack is NULL
 * @throws StackUnderflowException if stack is empty
 */
extern int stack_pop(int_stack * stack);
```

# Creating an exception context #

Now our stack component uses the exception handling framework, so we need to call stack functions in a proper context, i.e. within an exception context. Otherwise, the library will fail (by terminating the program) when, for example, a `throw` clause is found without an exception context.

```
#include <stdio.h>
#include "e4c.h"
#include "stack.h"

int main(int argc, char * argv[]){

    e4c_using_context(E4C_TRUE){

        /* now we can try, catch, throw, etc. */

    }

}

```

# Playing with `try/catch/finally` blocks #

Once we have begun our exception context, we are ready to go.

```
e4c_using_context(E4C_TRUE){

    int_stack stack;

    stack_construct(&stack, 3);

    try{
        stack_push(&stack, 100);
        stack_push(&stack, 200);
        stack_push(&stack, 300);
        /* the next push operation will throw an exception */
        stack_push(&stack, 400);
    }catch(StackException){
        printf("Error: %s\n", e4c_get_exception()->message);
    }finally{
        int last_pushed_item = stack_pop(&stack);
        printf("Last pushed item: %d\n", last_pushed_item);
        /* would print: 300 */
        stack_destruct(&stack);
    }
}
```

# Summary #

These are the basics of the library.

Using exceptions allows you to design more elegant interfaces. Your functions don't need to return values (or receive _out_ parameters) just for the sake of error handling. Remember to document the exceptions they may throw.

You need to set up an exception context before calling any of the exception handling functions or _keywords_. You can do it either in a simple code block, throught `e4c_using_context{...}` or in separate parts of the program, by calling `e4c_context_begin()` and `e4c_context_end()`.

Try it yourself and have fun using `exceptions4c`!


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)