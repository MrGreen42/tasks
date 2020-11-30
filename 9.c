#include <sys/vfs.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
                printf ("Incorrect usage\n");
                return 1;
        }
	struct statfs buf;
	if ((statfs(argv[1], &buf)) == -1) {
		printf("Failed to statfs");
		return 1;
	}
	printf("Total: %lu \n",buf.f_blocks * buf.f_bsize);
	printf("Avaliable: %lu\n", buf.f_bsize * buf.f_bavail);
	printf("Used: %lu\n",buf.f_bsize * buf.f_blocks - buf.f_bsize * buf.f_bavail);
	return 0;
}



