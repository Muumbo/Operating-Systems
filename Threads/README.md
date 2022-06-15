# Threads

#include <pthread.h>
**Always check if functions are threadsafe!!**
- examples for functions that are not threadsafe (not safe -> safe): <br />
    - rand() -> rand_r()


### create one thread

```
void* function(void* arg){
    exampleVar = *(int*)arg;

    return NULL;
    //or some pointer to a variable:
    //return &exampleVar;
}

//somewhere in main:
pthread_t thread;
pthread_create(&thread, NULL, &function, &arg)

pthread_join(thread, NULL)

//int* returnVar; (lets take int as example)
//pthread_join(thread,(void**) &returnVar);

```
### Thread struct and creation loop

**Use this struct:**
```
struct TrheadStruct {
    pthread_t*
    int* index;
}
```