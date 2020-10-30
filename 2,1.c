#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 
#include <unistd.h>


int main(int argc, char *argv[]) {
	int fildes, cfildes = 0;
	if (argc != 3) {
		printf ("Usage: %s some.file\n", argv[0]);
		return 1;
	}
	fildes = open(argv[1], O_APPEND | O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	printf("%d\n", fildes);
	perror("Condition");
	if (fildes == -1) {
		perror("Cannot create or modify file\n");
		
		return 1;
	}

	ssize_t nbytes =  write(fildes, argv[2], sizeof(argv[2]));
	if (nbytes == -1) {
		printf ("Error with writing\n");
		perror("error2");
                return 1;
	}
	if ((size_t) nbytes <  sizeof(argv[2])) {
                printf ("Writing is unsucessful\n");
        
        }
	cfildes = close(fildes);
	if (cfildes != 0) {
		printf ("Unsucessful closing\n");
                return 1;
	}
	
	return 0;

}
