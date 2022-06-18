#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <fcntl.h>
#define MQ_NAME "/csba1316"

    typedef struct{
        char msg[64];
    } message;

int main(int argc,char* argv[]){

    if (argc != 2){
        printf("usage: ./client <message>\n");
        return EXIT_FAILURE;
    }

    mqd_t mq = mq_open(MQ_NAME, O_WRONLY, S_IWUSR | S_IRUSR, NULL);
    if (mq == -1) {
        perror("mq_open()");
        return EXIT_FAILURE;
    }


    message msg_to_send = { 0 };
    snprintf(msg_to_send.msg, 64, "%s", argv[1]);
    printf("you sent: %s\n", msg_to_send.msg);

    if (mq_send(mq, (char*) msg_to_send.msg, sizeof(message), 1) < 0) {
        perror("ERROR-> mq_send()");
        mq_close(mq);
    }

    mq_close(mq);

return EXIT_SUCCESS;
}