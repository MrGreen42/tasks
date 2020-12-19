#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf ("Incorrect Usage. Programm needs file and string, which will be written into it");
		return 1;
	}
	int fildes = open(argv[1], O_APPEND | O_RDWR | O_CREAT, 0600);
	if (fildes == -1) {
		perror("Cannot create or modify file\n");
		
		return 1;
	}
	
	if (dprintf(fildes,"%s", argv[2]) < 0) {
                perror("Error with writing");
                return 1;
        }
	if (close(fildes) != 0) {
		perror("Unsucessful closing");
                return 1;
	}
	
	return 0;

}
