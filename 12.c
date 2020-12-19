#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char *argv[]) {
	printf("Process id: %d\n", getpid());
	printf("Process parent id: %d\n", getppid());
	struct passwd *pwd;
	if (!(pwd = getpwuid(getuid()))) {
		perror("Cannot get information of process");
		return 0;
	}
	printf("user id: %d\n", pwd->pw_uid);
	printf("user name: %s\n", pwd->pw_name);
	printf("group id: %d\n", pwd->pw_gid);
	return 0;
}
