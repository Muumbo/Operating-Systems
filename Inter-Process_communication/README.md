# Inter-Process communication
## Shared Memory
## Sockets
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
