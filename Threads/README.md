# Threads

#include <pthread.h>
**Always check if functions are threadsafe!!**
- examples for functions that are not threadsafe (not safe      ->      safe): <br />
    - rand()      ->      rand_r()


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
struct trheadStruct {
    pthread_t* thread;
    int* index;
}
```
**Use this loops**
```
for (int i=0; i<num_threads; i++){
    threadStruct.index[i] = i;
    if (pthread_create(&threadStruct.thread[i], NULL, &function, &threadStruct.index[i]) != 0){
        fprintf(stderr,"Error: pthread_create()\n");
    return EXIT_FAILURE;
    }
}
```
```
for (size_t i=0; i<num_guests;i++){
    if (pthread_join(threadStruct.thread[i], NULL) != 0){
        printf("error during pthread_join()\n");
        return EXIT_FAILURE;
    }
}
```
for (int i=0; i<num_threads; i++){
        threadStruct.index[i] = i;
        if (pthread_create(&threadStruct.thread[i], NULL, &function, &threadStruct.index[i]) != 0){
            fprintf(stderr,"Error: pthread_create()\n");
        return EXIT_FAILURE;
        }
    }