#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(void) 
{
    void sigint_handler(int sig);

    if(signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        perror("signal");
        exit(1);
    }

    int fd[2],num,buffer;
    pipe(fd);

    pid_t pid = fork();

    if(pid == 0)
    {
        close(fd[0]);
        printf("Enter a number:  ");
        scanf("%d", &num);
        write(fd[1], &num, sizeof(num));
        printf("Back to parent...\n");

        exit(EXIT_SUCCESS);
    }
    else if(pid > 0)
    {
        printf("Control to child process...\n");
        wait(NULL);
        close(fd[1]);
        read(fd[0], &buffer, sizeof(buffer));
        close(fd[0]);
	
	if(buffer >=0)
        {
		if(buffer == 0 || buffer == 1)
                {
                	printf("%d is not a prime number.\n", buffer);
			exit(EXIT_SUCCESS);
                }
                else
                {
                        for(int i = 2; i <= buffer / 2; i++)
                        {
                 	       if(buffer % i == 0)
                               {
                        	       printf("%d is not a prime number.\n", buffer);
                                       exit(EXIT_SUCCESS);
                               }
                               else
                               {
                                       printf("%d is a prime number.\n",buffer);
                                       exit(EXIT_SUCCESS);
                               }
			}
                        if(buffer == 2)
                        {
				printf("%d is a prime number.\n",buffer);
                                exit(EXIT_SUCCESS);
                        }
			else if(buffer == 3)
			{
				printf("%d is a prime number.\n",buffer);
	                        exit(EXIT_SUCCESS);
			}
                        printf("Job is done.\n");
                }
                perror("Error");
        }
        return EXIT_SUCCESS;

    }
}
void sigint_handler(int sig) 
{
    printf("You cant't end this!\n");
}
