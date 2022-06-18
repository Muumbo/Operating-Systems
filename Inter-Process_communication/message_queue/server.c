#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <mqueue.h>
#include <fcntl.h>
#define MQ_NAME "/csba1316"
#define maxmessages 10 //more than a certain amount generetes an error at mq_open
#define maxmsgsize 128

    typedef struct{
        char msg[64];
    } message;


int main(void) {
    const struct mq_attr attributes = {
        .mq_maxmsg = maxmessages,      /* Max. # of messages on queue */
        .mq_msgsize = maxmsgsize       /* MAX. size of single message */
    };
    const mode_t permissions = S_IRUSR | S_IWUSR; //600
    const int oflag = O_CREAT | O_RDONLY; // 64

    mqd_t mq = mq_open(MQ_NAME, oflag, permissions, &attributes);
    if (mq == -1){
        perror("mq_open()");
        return EXIT_FAILURE;
    }

    message msg_to_recieve = { 0 };

    printf("server shuts down on message \"quit\"\n\n");

    while (1){
        if (mq_receive(mq, (char*) &msg_to_recieve, maxmsgsize, NULL) < 0){
            perror("ERROR-> mq_recieve()\n");
            goto end;
        }
        printf("%s\n", msg_to_recieve.msg);
        if (!strncmp(msg_to_recieve.msg, "quit", 5)) {
            goto end;
        }
    }
    end:
    mq_close(mq);
    mq_unlink(MQ_NAME);

return EXIT_SUCCESS;
}