/*This code creates the queue and then waits for a message to come in.*/

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
    int msgsize = 1000;
    
    struct mq_attr attribute;           //initializing an attribute struct
    attribute.mq_msgsize = msgsize;     //setting max message size                         
    attribute.mq_maxmsg = 10;           //setting maximum number of messages in queue (we are only sending one message)
    //attribute.mq_flags = 0;

    mqd_t message_queue; // initializing message queue

    message_queue = mq_open("/mq", O_RDONLY|O_CREAT,&attribute); //Create message queue
    char recievestring[msgsize];                                 //String (or char array) to save message

    mq_receive(message_queue, recievestring, msgsize, 0);        //Read oldest message from queue (BLOCKING ACTION)

    //printf("%s\n", recievestring);    //testprint          

    int counter = 0;
    for (int i = 0; i < strlen(recievestring); i++)
    {
        if (recievestring[i] == ' ')    //counts spaces (technically not words but the amount of word is 1 more than spaces in a normal message)
            counter++;
    }
    counter + 1; 
    printf("number of words in textfile is: %d\n", counter); //prints out result

    mq_close(message_queue); //closes queue
    mq_unlink("/mq");       //deletes queue
}