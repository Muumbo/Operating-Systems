# Inter-Process communication
## Shared Memory
**#include <sys/mman.h>**
**#include <sys/stat.h>**
**#include <fcntl.h>**
**Link with -ltr**
```
int shm_open(const char *name, int oflag, mode_t mode);
```
- Creates or opens a shared memory object
- Shared memory object referred to by name
    - For portability reasons should start with “/”
    - Is not visible on the filesystem
- oflag is a bit mask indicating access type and whether shared memory should be
created or opened
- mode indicates the permissions for the shared memory object
- No memory is actually allocated
- Return value is a file descriptor to the shared memory object, or −1 on failure
```
int ftruncate(int fd, off_t length);
```

- Truncates a file referred to by the file descriptor to a given size
    - Can also be used to extend the size
- Must be used to actually allocate memory for the shared memory object
- Initializes extended memory to zero
- Return value of 0 indicates success
- Return value of −1 indicates failure
```
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
```
- Maps files or devices into process memory
- Must be used to actually map the shared memory object so it can be used
- addr can be NULL to let the kernel choose where the shared memory should be mapped
- length indicates the size of the shared memory to be mapped
- prot specifies desired memory protection (i.e. read, write, execute)
- flags should be MAP_SHARED for shared memory
- fd should be the file descriptor of the shared memory object
- offset indicates if the mapping should start at an offset
- The return value is pointer to the beginning of the mapped memory
    - Or MAP_FAILED on failure

**Shared memory Writer**
```
const char* name = "/shared_memory";
const int oflag = O_CREAT | O_EXCL | O_RDWR; // create, fail if exists, read+write
const mode_t permission = S_IRUSR | S_IWUSR; // 600
const int fd = shm_open(name, oflag, permission);
if(fd < 0) return EXIT_FAILURE;

const size_t shared_mem_size = 100;
if(ftruncate(fd, shared_mem_size) != 0) return EXIT_FAILURE;

char* shared_mem = mmap(NULL, shared_mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if(shared_mem == MAP_FAILED) return EXIT_FAILURE;

const char message[] = "Hello World";

//Some sinchronisation is required
memcpy(shared_mem, message, sizeof(message));
//Some sinchronisation is required

munmap(shared_mem, shared_mem_size);
close(fd);
shm_unlink(name);
```

**Shared memory Reader**
```
const char* name = "/shared_memory";
const int oflag = O_RDWR; // open read+write
const int fd = shm_open(name, oflag, 0);
if(fd < 0) return EXIT_FAILURE;

const size_t shared_mem_size = 100;
char* shared_mem = mmap(NULL, shared_mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if(shared_mem == MAP_FAILED) return EXIT_FAILURE;

char buffer[shared_mem_size];

//Some sinchronisation is required
memcpy(buffer, shared_mem, shared_mem_size);
//Some sinchronisation is required

munmap(shared_mem, shared_mem_size);
close(fd);

printf("%.*s\n", (int)shared_mem_size, buffer);
```
## Pipes
Data written to the write-end is buffered by the kernel
- Return value of 0 indicates success
- Return value of −1 indicates failure
```
int main(void) {
    int pipefd[2]; // pipefd[0]: read-end
                   // pipefd[1]: write-end

    if(pipe(pipefd) != 0) return EXIT_FAILURE;

    const pid_t cpid = fork();
    if(cpid == -1) return EXIT_FAILURE;

    if(cpid == 0) child(pipefd);
    else          parent(pipefd);
}
```
```
void parent(const int pipefd[2]) {
    close(pipefd[0]); // Close read-end

    const char* msg = "Hello World!";
    write(pipefd[1], msg, strlen(msg));
    close(pipefd[1]); // Close write-end
                      // -> reader will see EOF

    wait(NULL) // Wait for child
}
```
```
void child(const int pipefd[2]) {
    close(pipefd[1]); // Close write-end

    char buf;
    while(read(pipefd[0], &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1);
    }
    write(STDOUT_FILENO, "\n", 1);

    close(pipefd[0]); // Close read-end too
}
```
### Named Pipes (FIFO)
```
int mkfifo(const char *pathname, mode_t mode);
```
Creates the special FIFO file on the filesystem referred to by pathname
- File permissions are specified by mode
- Note: Actual file permissions are mode & ~umask
- Return value of 0 indicates success
- Return value of −1 indicates failure
<br />

**Named Pipe API-Reader:**
```
const char* name = "named_pipe";
const mode_t permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 644
if(mkfifo(name, permission) != 0) return EXIT_FAILURE;

const int fd = open(name, O_RDONLY);
if(fd < 0) return EXIT_FAILURE;

char buf;
while(read(fd, &buf, 1) > 0) {
    write(STDOUT_FILENO, &buf, 1);
}
write(STDOUT_FILENO, "\n", 1);

close(fd);
unlink(name);
```
**Named Pipe API-Writer**
```
const char* name = "named_pipe";
const int fd = open(name, O_WRONLY);
if(fd < 0) return EXIT_FAILURE;

const char* msg = "Hello World";
write(fd, msg, strlen(msg));

close(fd);
```

## Message Queue
**#include <time.h>**
**#include <mqueue.h>**
```
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
```
Creates or opens a message queue
- name identifies the queue
    - For portability reasons should start with “/”
    - Is not visible on the filesystem
- oflag is a bit mask indicating access type and whether queue should be created or opened
- mode indicates the permissions for the queue
- attr specifies message queue properties //NULL for standard attributes
    - be aware that a high value on some of the attributes might cause problems on mq_open
 <br />
I made a short example for a client-server interaction using a mq: https://github.com/Muumbo/Operating-Systems-PS-2022/tree/main/Inter-Process_communication/message_queue



## Sockets (usecase: Server - Clients)