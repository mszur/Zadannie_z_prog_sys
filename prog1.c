#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h> // open
#include <fcntl.h>     // open flags

int main(int argc, char* argv[])
{
    int X;
    int status;
	int pid;
	int fdfifo;
	int fd[2];
		//pipes_id[0] - read
		//pipes_id[1] - write
	//char buffer[32];
	int intbuf[1];




	if (pipe(fd) == 0) {

		pid = fork();
		if(pid == -1) { printf("fork error");	exit(EXIT_FAILURE);	}
		else if (pid == 0)
		{ //child
            int Y;  int ibuf[1];
			close(fd[1]); // close write
			read(fd[0] , ibuf , sizeof(int));
			Y=ibuf[0];
			printf("child read %d from pipe\n", Y);
			close(fd[1]);
			Y*=2;
			printf("Vaule of Y is %d \n", Y);
			ibuf[0]=Y;

        printf("WRITE\n");
            printf("Vaule of ibuf is %d \n", ibuf[0]);
        mkfifo("/tmp/my_fifo", 0666);

        fdfifo = open("/tmp/my_fifo", O_WRONLY);
		write(fdfifo, ibuf, sizeof(int));
		close(fdfifo);
		exit(EXIT_SUCCESS);


		} else if (pid > 0)
		{ //parent
		printf("Podaj liczbe calkowita:\n");
        scanf("%d", &X);
        intbuf[0]=X;
			close(fd[0]);	// close read
			write(fd[1], intbuf, sizeof(int));
			printf("parent write  %d to pipe \n", *intbuf);
			close(fd[1]);
			waitpid(pid, &status, 0);
		}
		}
    return 0;
}
