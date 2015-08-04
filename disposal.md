# Handling Resources #

Resources are objects we are required to **acquire** and **dispose** in order to _use_ them within our program. For example, a `FILE` needs to be `fopen`'ed and `fclose`'d.

When using resources, sometimes the part of the code that acquires the resource is far away in _space_ (in source code) or _time_ (in runtime) from the part that disposes it. But very often, resources are consecutively: **acquired**, **used** and then **disposed**, in a row.

In such times, manual acquisition (before) and disposal (after), before and after the real deal (actually _making use_ of the resource), feels like a cumbersome and tedious bookkeeping task.

This pattern goes like this:

  1. try to **acquire** the resource
  1. failed? then take the appropriate actions
  1. succeeded? then **use** the resource
  1. when done, **dispose** the resource

Note that the resource must be disposed, even if the code that uses the resource throws an exception.

When doing all this things _manually_, care must be taken to:
  * remember to dispose the resource in a `finally` block.
  * dispose the resource only if the acquisition succeeded.

`exceptions4c` brings you an elegant solution: the acquisition and disposal can be carried out implicitly by using any of these keywords:
  * **`with ... use`**
  * **`using`**

Either way, the following rules apply:
  * The acquisition is considered successful if no exception was thrown **during** the acquisition of the resource.
  * The resource is **guaranteed to be disposed** if (and only if) the acquisition succeeded, disregarding whichever exception was thrown **after** the acquisition.

# Syntax `with... use` #

This syntax lets you implicitly dispose resources. It has a `with` block which takes care of the acquisition and a `use` block which does anything with the resource. The disposal function will be automatically called according to the _Dispose Pattern_ semantics:

```
with(foo, dispose_foo){
    get_some_foo("bar", 123);
}use{
    do_something(foo);
}
```

`with` needs two arguments:
  1. The name of the variable representing the resource
  1. The name of the function or macro which will dispose the resource when finished

The disposal function (or macro) must accept two parameters:
  1. A parameter receiving the _resource_
  1. A boolean parameter representing whether the `use` block _failed_ or not

When the disposal function does not need to know if the `use` block did complete or not, you can define a macro which filters certain parameters to the actual function, and use that macro as the `disposal function`. For example:

```
# define dispose_file(_file_, _failed_) fclose(file)
```

Neither `with` nor `use` blocks need to be written between curly braces. In fact, the whole lot can be a single line.

```
with(foo, dispose_foo) get_some_foo("bar", 123); use do_something(foo);
```

# Syntax `using` #

This alternative syntax allows you to write terser sentences, leaving both acquisition and disposal out:

```
using(FOO, foo, ("bar", 123)){
    printf("foo: '%s', %d\n", foo.text, foo.number);
}
```

`using` needs three arguments:
  1. The name of the type of resource
  1. The name of the variable representing the resource
  1. The list of arguments to be passed to the acquisition function or macro

The name of the acquisition and disposal functions will be made up by appending the name of the type of resource to `e4c_acquire_...` and `e4c_dispose_...`. For example, if the type of resource is `FOO`, then the next functions or macros will be implicitly called:
  * `e4c_acquire_FOO`
  * `e4c_dispose_FOO`

The acquisition function (or macro) `e4c_acquire_X` must accept the specified list of _parameters_, as well as return a value assignable to the _variable_. The function (or macro) `e4c_dispose_X` must accept the same parameters as in the previous syntax (_resource_, _failed_).

# Handling Errors #

Errors regarding any of the acquisition, use or disposal of the resource can be handled right away, by adding `catch` or `finally` blocks to either a `using` or `with` block:

```

using(FOO, foo, ("bar", 123)){
    do_something(foo);
}catch(FooNotAcquiredException){
    /* ... */
}catch(FooFailedException){
    /* ... */
}finally{
    /* ... */
}

with(FOO, foo) get_some_foo("bar", 123) use{
    do_something(foo);
}catch(FooNotAcquiredException){
    /* ... */
}catch(FooFailedException){
    /* ... */
}finally{
    /* ... */
}

```

Just remember you don't need to dispose _manually_ the resource in the `finally` block.

# Customized `using` Macros #

If you are going to handle a specific type of resources very often, it can be handy to define simple macros, such as:

```
# define using_FOO(_var_, _arg1_, _arg2) using(FOO, _var_, (_arg1_, _arg2) )

/* this way, you can write: */

using_FOO(x, "hello", 31416) do_something(x);

/* instead of: */

using(FOO, x, ("hello", 31416) ) do_something(x);

```

You can save some parentheses and it looks cleaner.

# Reusing Legacy Code #

If you create your own resources and related functions, you can smooth the path by creating `e4c_acquire_X` and `e4c_dispose_X` functions.

However, if you don't have that luxury, you will probably need to reuse existing code which does not fullfill the requirements necessary to handle resources in this way, for example:
  * There's no `e4c_acquire_X` function
  * There's no `e4c_dispose_X` function
  * The acquisition does not throw any exception but returns NULL or something else.

Let's take a use case and see how can we work around it.

## Memory ##

Heap allocated memory is just one kind of resource we could need to use in this way:
  * Memory is acquired by calling `malloc`
  * Memory is disposed by calling `free`
  * Acquisition fails by returning NULL (instead of throwing an exception)

We could start by defining the macros

```
# define e4c_acquire_memory malloc
# define e4c_dispose_memory(_buffer_, _failed_) free(buffer)
```

Next, we realize we cannot use the keyword `using`:

```
void * buffer;
using( memory, buffer, (1024) ){
    memset(buffer, 0, 1024);
    /* what if malloc failed?? */
}
```

Instead, we need to throw an exception if `malloc` returned NULL. We can do this by using the alternative syntax (`with ... use`):

```
with(buffer, e4c_dispose_memory){
    buffer = e4c_acquire_memory(1024);
    if(buffer == NULL) throw(NotEnoughMemoryException);
}use{
    /* if we got here, malloc didn't fail */
    memset(buffer, 0, 1024);
}
```

Since this will be a recurring pattern, we could create a customized macro:

```
# define using_memory(_var_, _bytes_) \
    with(_var_, (_bytes_) ){ \
        _var_ = e4c_acquire_memory(1024); \
        if(_var_ == NULL) throw(NotEnoughMemoryException); \
    }use
```

This way we could write:

```
using_memory(buffer, 1024){
    memset(buffer, 0, 1024);
}
```

Of course, we can use this with in conjunction with `catch` or `finally` blocks:

```
using_memory(buffer, 1024){
    memset(buffer, 0, 1024);
}catch(NotEnoughMemoryException){
    /* ... */
}finally{
    /* ... */
}
```

There is already a small set of macros built into the framework which handle standard resources (memory, files) according to this style.


---


![http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png](http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png)