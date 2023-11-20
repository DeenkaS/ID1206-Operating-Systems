#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int fd[2];
    pipe(fd);                               // fd[0]==readend fd[1]==writeend
    int read = fd[0];                       // pointer for readability (completely unnecessary)
    int write = fd[1];                      // pointer for readability (completely unnecessary)

    pid_t pid = fork();

    if (pid == 0)
    {                                       // child process (or thread);
        char path[] = "ls";                 //name of file were running
        char *args[] = {path, "/", NULL};   //commands running
        system("ls /");                     //run ls once to get printout for assignment
        close(read);                        //close read end of pipe
        dup2(write, STDOUT_FILENO);         //redirect stdout through pipe
        close(write);                       //close write end of pipe
        execvp(path, args);                 //execute "ls /" from the ls file 
    }
    else if (pid > 0)
    {                                       // parent process (or thread);
        waitpid(0, 0, 0);


        close(write);                       //close write end
        dup2(read,STDIN_FILENO);            //redirect stdin through pipe
        close(read);                        //clsoe read end
        char path2[] = "wc";                //name of file were running
        char *args2[] = {path2, "-l", NULL}; //commands running
        execvp(path2, args2);               //execute "wp -l" from the wp file 

    }
    return 0;
}