#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h>	
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>


static void sighandler(int signo) {

	if(signo == SIGINT) {

		printf("Information on failure located in details.txt\n");

		int s = open("details.txt", O_WRONLY | O_CREAT);

		char * p = "Exited due to SIGINT\n";

		if (write(s,p,21) == -1) {
			//printf("%s\n", strerror(errno));
			exit(1);
		}

		close(s);

		exit(130);
	}

	if(signo == SIGUSR1) {
		printf("My parent's pid is: %d\n", getppid());
	}

}

int main() {

	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);

	while("true") {
		printf("My pid is: %d\n", getpid());

		sleep(1);
	}
	
	return 0;
}