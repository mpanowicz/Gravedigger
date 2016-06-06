#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>

using namespace std;

#define MAX_SIZE 256
#define readI(fd, x) read(fd, x, sizeof(int))
#define readF(fd, x) read(fd, x, sizeof(float))
#define writeI(fd, x) write(fd, x, sizeof(int))
#define writeF(fd, x) write(fd, x, sizeof(float))

int main(int argc, char** argv) {
	long currentTime = 0;
	while(1){
		int fd, con = 0;
		struct sockaddr_in sa;
		struct hostent* addrent;
		fd = socket(PF_INET, SOCK_STREAM, 0);
		addrent=gethostbyname("panowiczmichal.ddns.net");
		sa.sin_family = PF_INET;
		sa.sin_port = htons(8080);
		memcpy(&sa.sin_addr.s_addr, addrent->h_addr, addrent->h_length);
		con = connect(fd, (struct sockaddr*)&sa, sizeof(sa));
		int corpses = 0;
		if(con == 0){
			int count;
			int rank=atoi(argv[1]);
			long time;
			writeI(fd, &rank);
			readI(fd, &count);
			readI(fd, &time);
			if(time > currentTime){
				currentTime = time;
				corpses = count;
				printf("Corpses:%d Time:%ld\n", count, currentTime);
			}
			close(fd);
			//break;
		}
		close(fd);
	}
    return 0;
}
