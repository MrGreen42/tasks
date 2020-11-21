#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
        DIR* dirp;
	int drfd;
        if (argc != 2) {
                printf("incurrent number of arguments\n");
                return 1;
        }
        if ((dirp = opendir(argv[1])) == NULL) {
                perror("Cannot open the directory\n");
                return 1;
        }
        struct dirent *dir;
        struct stat stat_buf;
	if ((drfd = dirfd(dirp)) == -1) {
		perror("Cannot open the directory\n");
		return 1;
	}
        while ((dir = readdir(dirp)) != NULL ) {
                printf("File type: ");
                if ((dir->d_type) == DT_UNKNOWN) {
                        if (fstatat (drfd, dir->d_name, &stat_buf, 0) == -1) {
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
                        switch (dir->d_type) {
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
	}



        if (closedir(dirp) != 0) {
                perror("Failed to close directory\n");
                return 1;
        }
        return 0;
}

