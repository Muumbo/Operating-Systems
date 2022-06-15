# Synchronisation methods
As we are probably working with threads here's a short reminder: <br />
#include pthread.h <br />
compile with **-pthread** flag
## Mutex
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
### Atomic mutex
**#include <stdatomic.h>**
```
#define MUTEX_LOCK mutex_lock(&atomic_mutex);
#define MUTEX_UNLOCK mutex_unlock(&atomic_mutex);

atomic_flag atomic_mutex = ATOMIC_FLAG_INIT;

void mutex_lock(atomic_flag *x){
    while (atomic_flag_test_and_set(x)){}
}
void mutex_unlock(atomic_flag *x){
    atomic_flag_clear(x);
}

```
the two Mutex methods show similar (performance)stats.
Major differences are the System time, where the atomic-Mutex variant is showing no time at all. The standard Mutex on the other side uses less User time.
Also notable are the number of voluntary context switches, as they are reduced an insane amount in the atomic mutex variant.
## Semaphores
**#include <semaphore.h>**
```
sem_t semaphore;

void* funktion() {
    sem_post(&semaphore) //increases the Semaphore variable
    sem_wait(&semaphore) //decreases the Semaphore variable
}

int main() {

    sem_init(&semaphore, 0 if threads or 1 if processes, starting_value);

    sem_destroy(&semaphore);

}
```