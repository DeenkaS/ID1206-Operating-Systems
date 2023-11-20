/*This code reads the .txt file and sends the message. Start the other code first since it creates the queue*/

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <fcntl.h>

int main()
{

    mqd_t message_queue; // initializing message queue
    FILE *fptr;
    int msgsize = 1000;

    message_queue = mq_open("/mq", O_WRONLY);   //opens queue in write only

    char readstring[msgsize];           //string to save emssage

    fptr = fopen("readfile.txt", "r"); // open file in readmode

    
    fgets(readstring, msgsize, fptr);   //reads first line of file

    mq_send(message_queue, readstring, strlen(readstring), 0);    //sends message to message queue

    //printf("%s\n" , readstring);           //testprint

    mq_close(message_queue);        //closes message queue
}