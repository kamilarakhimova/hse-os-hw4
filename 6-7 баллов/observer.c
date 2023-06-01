#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("wrong number of arguments in the command line( \n please, add IP address and port");
        exit(-1);
    }
    char* server_ip = argv[1];
    int server_port = atoi(argv[2]);
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char sendline[256], recvline[256];
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("can't create socket");
        exit(1);
    }
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(3000); // server port = 3000
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr*) &cliaddr, sizeof(cliaddr)) < 0) {
        perror("can't connect to server");
        close(sockfd);
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);
    servaddr.sin_addr.s_addr = inet_addr(server_ip);
    char* message1 = "o";
    if (sendto(sockfd, message1, strlen(message1) + 1, 0, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("can't send message 1 to server");
        exit(1);
    }
    printf("Успешно установлено подключение наблюдателя к серверу.\n");
    for (;;) {
	char message2[256];
	socklen_t clntlen = sizeof(cliaddr);
        int symbols;
	if ((symbols = recvfrom(sockfd, message2, 256, 0, (struct sockaddr*) &cliaddr, &clntlen)) < 0) {
	    perror("can't get message");
	    close(sockfd);
	    exit(1);
        }
        message2[symbols] = '\0';
        printf("%s", message2);
        if ((strcmp(message2, "А вот и рассвет, экскурсия окончена. Всё, конец!\n") == 0)) {
            break;
        }
    }
    close(sockfd);
    return 0;
}
