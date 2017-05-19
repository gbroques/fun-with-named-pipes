/*
 ============================================================================
 Name        : program2.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Communicates with proj3
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int fd;
	char* myfifo = "/tmp/myfifo";	
	fd = open(myfifo, O_RDONLY);
	if (fd < 0) {
		perror("mkfifo");
		return EXIT_FAILURE;
	}
	int buf;
	int i = 0;
	int intPair[2];
	while (read(fd, &buf, sizeof(buf)) > 0) {
		intPair[i % 2] = buf;
		if (i % 2 == 1) {
			if (intPair[0] == 0 && intPair[1] == 0) {	
				close(fd);
				return i / 2;
			}
			int a = (((float) intPair[0]) / 2.0) + (((float) intPair[1]) / 2.0);
			int b = (((float) intPair[0]) / 2.0) - (((float) intPair[1]) / 2.0);
			printf("%d %d\n", a, b);
		}
		i++;
	} 
	close(fd);
	return EXIT_SUCCESS;
}
