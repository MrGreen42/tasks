#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>




int output(char *dir_name, int level) {
	int i, cmp1, cmp2;
	short int ifdir = 0;

	i = level;
	DIR* dirp;
	if ((dirp = opendir(dir_name)) == NULL) {
		perror("Cannot open the directory\n");
		return 1;
	}
	struct dirent *dir;
	struct stat stat_buf;
	
	
	while ((dir = readdir(dirp)) != NULL ) {
		while (i > 0) {
			printf("	");
			i = i - 1;
		}
		i = level;
		printf("File type: ");
		if ((dir->d_type) == DT_UNKNOWN) {
			if (lstat (dir->d_name, &stat_buf) == -1) {
                	        perror("Failed to stat");
        	                return 1;
	                }
	        	switch (stat_buf.st_mode & S_IFMT) {
        			case S_IFBLK:  printf("block device		");        break;
       	   			case S_IFCHR:  printf("character device		");        break;
          			case S_IFDIR:  printf("directory		");	   ifdir = 1;	     break;
         			case S_IFIFO:  printf("FIFO/pipe		");        break;
				case S_IFLNK:  printf("symlink			");        break;
	        		case S_IFREG:  printf("regular file		");        break;
	        		case S_IFSOCK: printf("socket			");        break;
	        		default:       printf("unknown?			");        break;
	        	}
		} else {
			switch (dir->d_type) {
				case DT_BLK:   printf("block device		");	   break;
				case DT_DIR:   printf("directory                ");        ifdir = 1;        break;
				case DT_CHR:   printf("character device         ");        break;
				case DT_FIFO:  printf("FIFO/pipe                ");        break;
                                case DT_LNK:   printf("symlink                  ");        break;
				case DT_REG:   printf("regular file             ");        break;
				case DT_SOCK:  printf("socket                   ");        break;
			}
		}
		cmp1 = strcmp (dir ->d_name,".");
		cmp2 = strcmp (dir ->d_name,"..");
		printf("Name: %s \n", dir->d_name);
		
		if ((ifdir == 1) && (cmp1 != 0) && (cmp2 != 0)) {
			char *dpath;
                	asprintf(&dpath, "%s/%s", dir_name, dir->d_name);
			output(dpath, level + 1);
		}

		ifdir = 0;

        }


	
	if (closedir(dirp) != 0) {
		perror("Failed to close directory\n");
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
                printf("incurrent number of arguments\n");
                return 1;
        }
	output(argv[1], 0);
	return 0;
}
