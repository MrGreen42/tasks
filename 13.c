#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>

void pinfo(void) {

	printf("Process id: %d\n", getpid());
	printf("Process parent id: %d\n", getppid());
	struct passwd *pwd;
	if (!(pwd = getpwuid(getuid()))){
		perror("petpwuid");
	} else {
		printf("user id: %d\n", pwd->pw_uid);
		printf("user name: %s\n", pwd->pw_name);
		printf("group id: %d\n", pwd->pw_gid);
	}
}

int main(void)
{
	pid_t child_id = fork();	
	switch (child_id) {
		case -1:
			perror("Error with fork");
			return 1;
		case 0:
			printf("child:\n");
			pinfo();
			return 0;
		default:
			wait(NULL);
			printf("parent:\n");
			pinfo();
			return 0;
	}
	return 0;
}
