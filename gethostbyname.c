#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	size_t i = 0;
	const struct hostent *hp = gethostbyname("www.washington.edu");
	if (hp == 0) {
		perror("unable to lookup host\n");
		return -1;
	}
	if (hp -> h_addrtype == AF_INET) {
		printf("address type: AF_INET\n");
	}else if (hp -> h_addrtype == AF_INET6) {
		printf("address type: AF_INET6\n");
	}
	while (hp -> h_addr_list[i]) {
		printf("%s\n", inet_ntoa(*(struct in_addr*)(hp -> h_addr_list[i++])));
	}
	return 0;
}
