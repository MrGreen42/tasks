#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 512


int main(int argc, char *argv[]) {
	char buf[BUFSIZE];
	ssize_t nbytes, nbytes_w;
	struct stat stat_buf;
        if (lstat (argv[1], &stat_buf) == -1) {
                perror("Error with file to copy");
                return 2;
        }
	if (((stat_buf.st_mode) & (S_IFMT)) != S_IFREG) {
		printf("File to copy is not regular file\n");
		return 1;
	}
        if (argc != 3) {
                printf ("Incorrect usage\n");
                return 1;
        }
        int fildes_r = open(argv[1], O_RDONLY);
        if (fildes_r == -1) {
                perror("Cannot open fileto read\n");
                return 1;
        }
	int fildes_w = open(argv[2], O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
        if (fildes_w == -1) {
                perror("Cannot open file to write\n");
                return 1;
        }
	size_t nbytes_r;
	while ((nbytes_r = read(fildes_r, buf, BUFSIZE)) > 0) {
		nbytes = nbytes_r;
		while (nbytes) {
			nbytes_w = write(fildes_w, &buf[nbytes_r - nbytes], nbytes);
			nbytes = nbytes - nbytes_w;
		}
	}
        int cfildes_r = close(fildes_r);
        if (cfildes_r != 0) {
                printf ("Unsucessful closing\n");
                return 1;
        }
	int cfildes_w = close(fildes_w);
        if (cfildes_w != 0) {
                printf ("Unsucessful closing\n");
                return 1;
        }
        return 0;

}

