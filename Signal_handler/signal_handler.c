#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



void signal_handler(int signal){

    if (signal == SIGINT){
        // printf is NOT safe in a signal handler!!! (code can be interrupted at any moment);
        // You can check all safe functions in man signal-safety!
        write(STDOUT_FILENO, "\nSIGINT caught!\n", 15); // STDOUT_FILENO is fd of stdout
    }

    if (signal == SIGUSR1){
        write(STDOUT_FILENO, "\nSIGUSR1 caught!\n", 16);
    }

    if (signal == SIGTERM){
        write(STDOUT_FILENO, "\nSIGTERM caught!\n", 16);
    }

    if (signal == SIGKILL){
        write(STDOUT_FILENO, "\nSIGKILL caught!\n", 16);
    }

    while (1) {
        usleep(1);
    }
}

int main () {
    struct sigaction sa = {
    .sa_handler = signal_handler,
    };

    // Additionally initialize sa_mask, see sigaction(2) and sigsetops(3).
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL); // (signal, action, old action)
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGKILL, &sa, NULL); // note that SIGKILL cannot get caught even if you try

    while(1){
        printf("I wont terminate! (SIGKILL can't get caught) %d\n", getpid());
    }
    return EXIT_SUCCESS;
}