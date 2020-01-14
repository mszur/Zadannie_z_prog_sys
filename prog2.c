#include <stdio.h>
#include <string.h>    // strlen
#include <stdlib.h>    // EXIT_SUCCESS
#include <unistd.h>    // read,write
#include <sys/types.h> // open
#include <sys/stat.h>  // mkfifo
#include <fcntl.h>     // open flags

int main(int argc, char* argv[])
{ 
	int fptr;
	int   fd; 
	int intbuf;
	
	printf("Read from pipe\n");
		
		
		fd = open("/tmp/my_fifo", O_RDONLY);
		
		
			read(fd,&intbuf, sizeof(int));
			printf("read -  %d \n", intbuf);			
		unlink("/tmp/example_fifo"); // delete fifo
		close(fd);

	fptr = open("/dev/mydevice",O_WRONLY);
	if (fptr == 0) { 
	printf("Error opening device\n");

	return -1;

	}

	else {
	printf("Device open\n");

	write(fptr,&intbuf,sizeof(intbuf));
	printf("Value %d send to character device\n", intbuf);
	}

	close(fptr);
	printf("Device closed\n");
return 0;
}
