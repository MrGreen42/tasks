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
	off_t offset_r = 0, offset_w = 0;
	while ((nbytes = pread(fildes_r, buf, BUFSIZE, offset_r)) > 0) {
		offset_r =+ nbytes;
		while (nbytes) {
			nbytes_w = pwrite(fildes_w, buf, nbytes, offset_w);
			nbytes = nbytes - nbytes_w;
			offset_w += nbytes_w;
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

