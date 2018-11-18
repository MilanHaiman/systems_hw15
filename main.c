#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int* getrand() {
	int fd = open("/dev/random", O_RDONLY);
	if(fd == -1) {
		printf("Errno: %d\n", errno);
	}
	// printf("%d\n", fd);
	int * answer = malloc(sizeof(int));
	read(fd, answer, sizeof(int));
	close(fd);
	return answer;
}

int abs(int n) {
	if (n < 0) return -n;
	else return n;
}

int main(int argc, char const *argv[]) {

	printf("some initial message\n");
	int f1 = fork();
	if (f1)
	{
		int f2 = fork();
		if (f2)
		{
			int status;
			int childpid = wait(&status);
			printf("child with pid %d slept for %d seconds\n", childpid, WEXITSTATUS(status));
			printf("parent is done\n");
			return 0;
		}
		else {
			printf("%d\n", getpid());
			int *randnum = getrand();
			int seconds = (5 + (abs(*randnum) % 16));
			free(randnum);
			sleep(seconds);
			printf("child is done, slept for %d seconds\n", seconds);
			return seconds;
		}
	}
	else {
		printf("%d\n", getpid());
		int *randnum = getrand();
		int seconds = (5 + (abs(*randnum) % 16));
		free(randnum);
		sleep(seconds);
		printf("child is done, slept for %d seconds\n", seconds);
		return seconds;
	}
}