/*
 ============================================================================
 Name        : proj3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : cs2750 proj3
 ============================================================================
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	char* myfifo = "/tmp/myfifo";
	int fd, pid, status;
	mkfifo(myfifo, 0777);
	pid = fork();

	if (pid < 0) {
		perror("fork()");
		return EXIT_FAILURE;
	}

	if (pid == 0) {
		execlp("program2", "program2", (char*) NULL);
		perror("program2");
		_exit(EXIT_FAILURE);
	}

	fd = open(myfifo, O_WRONLY);
	if (fd < 0) {
		printf("Error: %d\n", errno);
		perror("myfifo");
		return EXIT_FAILURE;
	}
	int num;
	int i = 0;
	int intPair[2];	
	while (scanf("%d", &num) > -1) {
		intPair[i % 2] = num;
		if (i % 2 == 1) {	
			int sum = intPair[0] + intPair[1];
			int diff = intPair[0] - intPair[1];
			write(fd, &sum, sizeof(sum));
			write(fd, &diff, sizeof(diff));
		}
		i++;
	}	
	wait(&status);
	printf("Pairs read: %d\n", status / 256);
	close(fd);
	unlink(myfifo);
	return EXIT_SUCCESS;
}
