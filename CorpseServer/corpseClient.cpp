#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256
#define readI(fd, x) read(fd, x, sizeof(int))
#define readF(fd, x) read(fd, x, sizeof(float))
#define writeI(fd, x) write(fd, x, sizeof(int))
#define writeF(fd, x) write(fd, x, sizeof(float))

int main(int argc, char** argv) {
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
		if(con == 0){
			int count;
			int rank=1;
			writeI(fd, &rank);
			readI(fd, &count);
			printf("Corpses:%d\n", count);
			close(fd);
			break;
		}
		close(fd);
	}
    return 0;
}
