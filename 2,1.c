#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int fildes, cfildes = 0;
	if (argc != 3) {
		printf ("Incorrect Usage");
		return 1;
	}
	fildes = open(argv[1], O_APPEND | O_RDWR | O_CREAT, 00600);
	if (fildes == -1) {
		perror("Cannot create or modify file\n");
		
		return 1;
	}
	int size = strlen(argv[2]);
	ssize_t nbytes =  write(fildes, argv[2], size);
	if (nbytes == -1) {
		printf ("Error with writing\n");
		perror("error2");
                return 1;
	}
	if ((int) nbytes <  size) {
                printf ("Writing is unsucessful\n");
        
        }
	cfildes = close(fildes);
	if (cfildes != 0) {
		perror("Unsucessful closing");
                return 1;
	}
	
	return 0;

}
