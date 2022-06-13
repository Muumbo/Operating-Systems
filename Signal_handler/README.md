# Signal Handler
Good for catching termination signal and free your resources before ending your process.

## Struct form:
struct sigaction sa = {
    .sa_handler = signal_handler,
    };