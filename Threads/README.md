# Threads

#include <pthread.h>

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
kk