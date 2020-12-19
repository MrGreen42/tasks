#include <dirent.h>  
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>


struct linux_dirent {
	long           d_ino;
	off_t          d_off;
	unsigned short d_reclen;
	char           d_name[];
};

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
	int dirp;
	int nread;
	char buf[BUF_SIZE];
	struct linux_dirent *dir;
	int bpos;
	char d_type;
	struct stat stat_buf;
	if (argc != 2) {
		printf("incurrent number of arguments\n");
		return 1;
	}
	if ((dirp = open(argv[1], O_RDONLY | O_DIRECTORY)) == -1) {
		perror("Cannot open the directory\n");
		return 1;
	}
	for ( ; ; ) {
		nread = syscall(SYS_getdents, dirp, buf, BUF_SIZE);
		if (nread == -1) {
			perror("Fail to getdents\n");
			return 1;
		}
		if (nread == 0) {
			break;
		}
		for (bpos = 0; bpos < nread;) {
			dir = (struct linux_dirent *) (buf + bpos);
			d_type = *(buf + bpos + dir->d_reclen - 1);
			if ((d_type) == DT_UNKNOWN) {
				if (lstat (dir->d_name, &stat_buf) == -1) {
					perror("Failed to stat");
					return 1;
				}
				switch (stat_buf.st_mode & S_IFMT) {
					case S_IFBLK:  printf("block device             ");        break;
					case S_IFCHR:  printf("character device         ");        break;
					case S_IFDIR:  printf("directory                ");        break;
					case S_IFIFO:  printf("FIFO/pipe                ");        break;
					case S_IFLNK:  printf("symlink                  ");        break;
					case S_IFREG:  printf("regular file             ");        break;
					case S_IFSOCK: printf("socket                   ");        break;
					default:       printf("unknown?                 ");        break;
				}
			} else {
				switch (d_type) {
					case DT_BLK:   printf("block device             ");        break;
					case DT_DIR:   printf("directory                ");        break;
					case DT_CHR:   printf("character device         ");        break;
					case DT_FIFO:  printf("FIFO/pipe                ");        break;
					case DT_LNK:   printf("symlink                  ");        break;
					case DT_REG:   printf("regular file             ");        break;
					case DT_SOCK:  printf("socket                   ");        break;
				}
			}
			printf("Name: %s \n", dir->d_name);
			bpos += dir->d_reclen;
		}
	}
	return 0;
}

