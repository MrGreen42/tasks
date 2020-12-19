#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int last_sig;

void sig_handler(int val) {
	last_sig = val;
}

int main() {
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		perror("failed to SIGINT");
		return 1;
	}
	if (signal(SIGQUIT, sig_handler) == SIG_ERR) {
		perror("failed to SIGQUIT");
		return 1;
	}
	if (signal(SIGTERM, sig_handler) == SIG_ERR) {
		perror("failed to SIGTERM");
		return 1; 
	}
	while(1) {
		printf("im alive\n");
		pause();
		switch (last_sig) {
			case SIGINT:
				printf("^C doesnt't work\n"); break;
			case SIGQUIT:
				printf("^\\ doesn't work\n"); break;
			case SIGTERM:
				printf("SIGTERM doesn't work\n"); break;
			default:
				printf("unknown signal"); break;
		}
	}
	return 0;
}
