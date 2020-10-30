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
	int nbytes = 1;
	dprintf(fildes,"%s", argv[2]);
        if (nbytes < 0) {
                perror("Error");
                return 1;
        }
	cfildes = close(fildes);
	if (cfildes != 0) {
		perror("Unsucessful closing");
                return 1;
	}
	
	return 0;

}
