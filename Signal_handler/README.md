# Signal Handler
Good for catching termination signal and free your resources before ending your process.

You need to compile define _POSIX_C_SOURCE when compiling in order to use sigaction() 
> see $man sigaction

## Struct form:
```
struct sigaction sa = {
    .sa_handler = signal_handler,
    };
```