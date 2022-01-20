#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include<stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <linux/limits.h>

#define INPUT_LIMIT 100
#define ARG_LIMIT 10
#define LOG_LIMIT 200

void myShell();

void cd(char* args[],char* path)
{
    //Change Directory
    if(chdir(args[1])==-1)
    {
        printf("Error changing directory\n");
    }
}

bool input(char* args[],char* path)
{
    for(int j=0; j<ARG_LIMIT; j++)
    {
        //malloc for arguments input
        args[j]=malloc(INPUT_LIMIT);
    }
    char input[INPUT_LIMIT];
    int i=0;
    bool waitFlag=true;

    //PATH_MAX defined in linux/limit.h
    getcwd(path,PATH_MAX);
    printf("%s:$ ",path);

    fgets(input,INPUT_LIMIT,stdin);

    //remove \n at the end of input string
    if(input[strlen(input)-1] == '\n')
    {
        input[strlen(input)-1] = '\0';
    }
    //in case of empty input
    if(strlen(input)==0)
    {
        printf("No Command Entered !!\n");
        myShell();
    }
    else
    {

        char* token = strtok(input," ");

        do
        {
            //wait or no wait
            if(strcmp(token,"&")!=0)
            {
                strcpy(args[i++],token);
            }
            else
            {
                waitFlag=false;
            }
            token = strtok(NULL," ");

        }
        while(token != NULL);

        args[i]=NULL;
    }

    return waitFlag;
}

void handle_terminate(int sig, siginfo_t *info)
{
    //get current date & time
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    char str[LOG_LIMIT];

    //make string to log
    snprintf(str,LOG_LIMIT,"Child Process was Terminated id(%d) : %s",info->si_pid, asctime (timeinfo));

// Use write because async-safe function
    write(3,str,strlen(str));
}

void myShell()
{
    char *path = malloc(PATH_MAX);

    while(1)
    {
        char* args[ARG_LIMIT];
        bool waitFlag=input(args,path);

        //use SIGCHLD to know when child has been terminated
        struct sigaction sa;
//      sa.sa_sigaction = &handle_terminate;
        sa.sa_handler = &handle_terminate;
        sa.sa_flags = SA_SIGINFO|SA_RESTART;
        sigaction(SIGCHLD,&sa,NULL);

        if(strcmp(args[0],"exit")==0)
        {
            exit(EXIT_SUCCESS);
        }

        if(strcmp(args[0],"cd")==0)
        {
            cd(args,path);
        }
        else
        {

            pid_t p = fork();
            if(p==-1)
            {
                printf("There is an error while calling fork()");
            }
            if(p==0)
            {
                printf("Child process starting....\n");
                printf("Process:%s --> id(%d)\n",args[0],getpid());
                int error = execvp(args[0],args);

                if(error == -1)
                {
                    printf("This is not a valid Command!!!!\n");
                }
                exit(EXIT_SUCCESS);

            }
            else
            {
                sleep(2);
                if(waitFlag)
                {
                    printf("Parent procces waiting....id(%d)\n",p);
                    waitpid(p,NULL,0);
                }
            }
        }
    }
}



int main()
{
    //0777 read,write,execute for any user
    int log = open("log.txt",O_WRONLY | O_APPEND | O_CREAT,0777);
    if(log==-1)
    {
        printf("Error in reading file!\n");
    }

    myShell();
    close(log);
    return 0;
}
