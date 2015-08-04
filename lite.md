# Lightweight Version #

**exceptions4c lightweight version** is targeted at small projects and embedded systems. Use it when you just want to handle error conditions that may occur in your program through a simple yet powerful exception handling mechanism. It provides the **core functionality** of **exceptions4c** in less than 200 source lines of code.

## Download ##

Here you can download the latest version:

  * https://exceptions4c.googlecode.com/svn/downloads/exceptions4c-lightweight.zip

## Features ##

Some features available in lightweight version:

  * **ANSI C**: Written in good _old-fashioned_ C; no external dependencies. Available as two portable files (`e4c_lite.h` and `e4c_lite.c`) that can be easily integrated into another project.
  * **Plug and play**: No need to initialize/finalize it. Just `#include "e4c_lite.h"` and you're ready to use [try](keywords#try.md), [catch](keywords#catch.md), [finally](keywords#finally.md) or [throw](keywords#throw.md).
  * **Exception Hierarchies**: You can organize your own exception types [hierarchically](hierarchies.md); exceptions can be [caught](keywords#catch.md) through its supertype.
  * **Small overhead**: Implemented through a few optimized functions and a handful of macros. Functions take really few parameters. The smallest sufficient data types are used. Struct fields are ordered by size to reduce padding.
  * **No recursion**: Recursive calls were replaced by simple loops.
  * **Static allocation**: A static pool is used. No dynamic allocation; no fragmentation. The size of the pool may be configured to tweak your program's memory footprint.

## Non-features ##

Some features not available in lightweight version:

  * [assert](keywords#assert.md)
  * [throwf](keywords#throwf.md)
  * [repeat](keywords#repeat.md) or [rethrow](keywords#rethrow.md)
  * [use](keywords#use.md)... [with](keywords#with.md) ([Dispose patern](features#Dispose_Pattern.md))
  * [signal handling](signals.md)
  * [uncaught handler](uncaught.md)
  * [multithreading support](threads.md)

If you really need any of these, you should use **exceptions4c standard version**.

## Usage ##

  * **`E4C_DECLARE_EXCEPTION(name)`**: declares an exception type.
  * **`E4C_DEFINE_EXCEPTION(name, default_message, supertype)`**: defines an exception type.
  * **`try`**: introduces a block of code aware of exceptions.
  * **`catch(type)`**: introduces a block of code capable of handling a specific `type` of exceptions.
  * **`finally`**: introduces a block of code responsible for cleaning up the previous exception-aware block.
  * **`throw(type, message)`**: signals an exceptional situation represented by an exception object.
  * **`E4C_EXCEPTION`**: retrieves current thrown exception.

## Example ##

  * stack.h
```
# include "e4c_lite.h"

E4C_DECLARE_EXCEPTION(StackException);
E4C_DECLARE_EXCEPTION(StackOverflowException);
E4C_DECLARE_EXCEPTION(StackUnderflowException);

struct stack{ ... };

extern void stack_init(struct stack * s, int max);
extern void stack_push(struct stack * s, int value);
extern int stack_pop(struct stack * s);
```

  * stack.c
```
# include "stack.h"

E4C_DEFINE_EXCEPTION(StackException, "Stack error!", RuntimeException);
E4C_DEFINE_EXCEPTION(StackOverflowException, "Overflow!", StackException);
E4C_DEFINE_EXCEPTION(StackUnderflowException, "Underflow!", StackException);

void stack_push(struct stack * s, int value){
  if( stack_full() ) throw(StackOverflowException, "Too many values!");
  ...
}

int stack_pop(struct stack * s){
  if( stack_empty() ) throw(StackUnderflowException, NULL); /* default message will be used */
  ...
}

void stack_init(struct stack * s, int max){
  ...
}
```

  * main.c
```
# include "stack.h"

int main(int argc, char *argv[]){

  struct stack s;

  try{
    stack_init(&s, 2);

    stack_push(&s, 10);
    stack_push(&s, 100);
    stack_push(&s, 1000); /* will throw StackOverflowException */

    printf("This won't be printed");

  }catch(StackUnderflowException){

    printf("This won't be printed either");

  }catch(StackException){

    /* this block will be executed because StackOverflowException "is-a" StackException */
    
    printf("Caught overflow: %s.", E4C_EXCEPTION.message);

  }finally{

    printf("Cleaning up...");
  }

  stack_push(&s, 123); /* will halt the program */

  printf("This won't be printed");

  return(123); /* program already yielded EXIT_FAILURE due to uncaught exception */
}
```

## Tweaks ##

You may define these _compiler-time_ parameters:

  * **`E4C_MAX_FRAMES`**: Maximum number of nested `try` blocks allowed in your program. It impacts the size of the static pool.
  * **`E4C_MESSAGE_SIZE`**: Maximum length (in bytes) of an exception message.
  * **`E4C_NOKEYWORDS`**: When defined, `try`, `catch`, `finally` and `throw` macros are not defined (you can still use: `E4C_TRY`, `E4C_CATCH`, `E4C_FINALLY` and `E4C_THROW` though).
  * **`NDEBUG`**: When defined, exceptions don't store _file/line_ information.

**exceptions4c lightweight version** is licensed under the **GNU Lesser General Public License**.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)