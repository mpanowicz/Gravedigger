#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#define readI(fd, x) read(fd, x, sizeof(int))
#define readF(fd, x) read(fd, x, sizeof(float))
#define writeI(fd, x) write(fd, x, sizeof(int))
#define writeF(fd, x) write(fd, x, sizeof(float))

using namespace std;

void childend(int signum)
{
	wait(NULL);
	printf("Koniec połączenia\n");
}

int main(int argc, char** argv) {
    unsigned int fdc, size, on=1; //client
    struct sockaddr_in lsa; //server
    struct sockaddr_in laddr; //client
	if(signal(SIGCHLD, childend) == SIG_IGN)
		signal(SIGCHLD, SIG_IGN);
	
	fdc = socket(PF_INET, SOCK_STREAM, 0);
	lsa.sin_family = PF_INET;
	lsa.sin_port = htons(8080);
	lsa.sin_addr.s_addr = INADDR_ANY;
	bind(fdc, (struct sockaddr*)&lsa, sizeof(lsa));
	listen(fdc, 10);
	
	size=sizeof(laddr);

	int fd2;
	while(1){
		fd2 = accept(fdc, (struct sockaddr*)&laddr, &size);
		if(!fork()){
			close(fdc);
			int rank;
			readI(fd2, &rank);
			int count = 1;
			printf("Nowe połączenie: %i\n", rank);
			writeI(fd2, &count);
			close(fd2);
			return 0;
		}
	}
    return 0;
}