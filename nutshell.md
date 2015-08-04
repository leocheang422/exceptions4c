# What #

**`exceptions4c`** is an exception handling framework for C.

# Why #

Because it's way more convenient to treat errors as exceptions, rather than checking the status of the last operation.

# When #

  * **`try`**: when a block of code is aware of the possibility that some exception can be thrown within it.
  * **`finally`**: when a block of code needs to clean things up, regardless of any exception.
  * **`throw`**: when some part of the program finds an error that can't handle, or something really bad happens: division by zero, segmentation fault, etc...
  * **`catch`**: ...the flow of the program jumps to a block of code that is able to handle the error.

# Where #

Cleaning up:

```
void * buffer = malloc(1024);

try{
    int bar = foo(buffer);
}finally{
    free(buffer);
}
```

Ensuring preconditions:

```
int stack_pop(Stack * stack){

    if(stack->elements == 0){
        throw(EmptyStackException);
    }

    stack->elements--;

    ...
}
```

Recovering from errors:

```
int * pointer = NULL;

try{
    int oops = *pointer;
}catch(BadPointerException){
    printf("No problem ;-)");
}

...
```

# How #

  * Drop the `e4c.h` and `e4c.c` in your project.
  * **`#include`** `"e4c.h"`
  * Create a `e4c_using_context` code block in `main`.

```
int main(int argc, char * argv[]){

    e4c_using_context(E4C_TRUE){
        try{
            ...
            if(error) throw(MyException, "Some error happened.");
            ...
        }catch(NullPointerException){
            ...
        }finally{
            ...
        }
    }
}
```


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)