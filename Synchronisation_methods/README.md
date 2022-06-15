# Synchronisation methods
## Mutex
#include pthread.h <br />
compile with **-pthread** flag
```
//I recommend to define this two methods for more readability
#define LOCK_MUTEX pthread_mutex_lock(&mutex);
#define UNLOCK_MUTEX pthread_mutex_unlock(&mutex);

pthread_mutex_t mutex;

int main () {
    pthread_mutex_init(&mutex, NULL);

    //code

    pthread_mutex_destroy(&mutex);
}


```