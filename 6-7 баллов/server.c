#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

#define MAX_CLIENTS 2
#define MAX_OBSERVERS 1

struct sockaddr_in client_sockets[MAX_CLIENTS];
struct sockaddr_in observer_sockets[MAX_OBSERVERS];
char observer_message[256];
int observer_symbols;

int sockfd;

void send_observer(char* message) {
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr*) &observer_sockets[0], sizeof(observer_sockets[0])) < 0) {
        perror("can't send messsage to observer");
        exit(1);
    }
}

void room_single_add(int client_sex, int room_add, int* single_rooms) {
    if (single_rooms[room_add] == 10) {
        single_rooms[room_add] = client_sex;
        if (client_sex == 1) {
            printf("Клиентка-дама заселилась в одноместный номер %d.\n", room_add + 1);
            sprintf(observer_message, "Клиентка-дама заселилась в одноместный номер %d.\n", room_add + 1);
            send_observer(observer_message);
        } else {
            printf("Клиент-джентльмен заселился в одноместный номер %d.\n", room_add + 1);
            sprintf(observer_message, "Клиент-джентльмен заселился в одноместный номер %d.\n", room_add + 1);
            send_observer(observer_message);
        }
    } else {
        if (client_sex == 1) {
            printf("Клиентка-дама не смогла заселиться в одноместный номер ");
            sprintf(observer_message, "Клиентка-дама не смогла заселиться в одноместный номер ");
            send_observer(observer_message);
        } else {
            printf("Клиент-джентльмен не смог заселиться в одноместный номер ");
            sprintf(observer_message, "Клиент-джентльмен не смог заселиться в одноместный номер ");
            send_observer(observer_message);
        }
        printf("%d, так как он уже занят.\n", room_add + 1);
        sprintf(observer_message, "%d, так как он уже занят.\n", room_add + 1);
        send_observer(observer_message);
    }
}

void room_double_add(int client_sex, int room_add, int* double_rooms) {
    if (double_rooms[room_add] == 10 || double_rooms[room_add + 15] == 10) {
        if (double_rooms[room_add] != 10) {
            if (double_rooms[room_add] == client_sex) {
                double_rooms[room_add + 15] = client_sex;
                if (client_sex == 1) {
                    printf("Клиентка-дама заселилась второй в двухместный номер %d.\n", room_add + 1);
                    sprintf(observer_message, "Клиентка-дама заселилась второй в двухместный номер %d.\n", room_add + 1);
                    send_observer(observer_message);
                } else {
                    printf("Клиент-джентльмен заселился вторым в двухместный номер %d.\n", room_add + 1);
                    sprintf(observer_message, "Клиент-джентльмен заселился вторым в двухместный номер %d.\n", room_add + 1);
                    send_observer(observer_message);
                }
            } else {
                if (client_sex == 1) {
                    printf("Клиентка-дама не смогла заселиться в двухместный номер ");
                    sprintf(observer_message, "Клиентка-дама не смогла заселиться в двухместный номер ");
                    send_observer(observer_message);
                } else {
                    printf("Клиент-джентльмен не смог заселиться в двухместный номер ");
                    sprintf(observer_message, "Клиент-джентльмен не смог заселиться в двухместный номер ");
                    send_observer(observer_message);
                }
                printf("%d, так как одно место в нём уже занято клиентом противоположного пола.\n", room_add + 1);
                sprintf(observer_message, "%d, так как одно место в нём уже занято клиентом противоположного пола.\n", room_add + 1);
                send_observer(observer_message);
            }
        } else {
            double_rooms[room_add] = client_sex;
            if (client_sex == 1) {
                printf("Клиентка-дама заселилась первой в двухместный номер %d.\n", room_add + 1);
                sprintf(observer_message, "Клиентка-дама заселилась первой в двухместный номер %d.\n", room_add + 1);
                send_observer(observer_message);
            } else {
                printf("Клиент-джентльмен заселился первым в двухместный номер %d.\n", room_add + 1);
                sprintf(observer_message, "Клиент-джентльмен заселился первым в двухместный номер %d.\n", room_add + 1);
                send_observer(observer_message);
            }
        }
    } else {
        if (client_sex == 1) {
            printf("Клиентка-дама не смогла заселиться в двухместный номер ");
            sprintf(observer_message, "Клиентка-дама не смогла заселиться в двухместный номер ");
            send_observer(observer_message);
        } else {
            printf("Клиент-джентльмен не смог заселиться в двухместный номер ");
            sprintf(observer_message, "Клиент-джентльмен не смог заселиться в двухместный номер ");
            send_observer(observer_message);
        }
        printf("%d, так как он уже занят.\n", room_add + 1);
        sprintf(observer_message, "%d, так как он уже занят.\n", room_add + 1);
        send_observer(observer_message);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("wrong number of arguments in the command line( \n please, add port number");
        exit(1);
    }
    int server_port = atoi(argv[1]);
    struct sockaddr_in servaddr, clientaddr;
    char line[256];
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("can't create socket");
        exit(1);
    }
    if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("can't bind socket");
        exit(1);
    }
    printf("server ip address = %s\n", inet_ntoa(clientaddr.sin_addr));
    srand(time(NULL));
    int single_rooms[10];
    for (int i = 0; i < 10; ++i) {
        single_rooms[i] = 10;
    }
    int double_rooms[30];
    for (int i = 0; i < 30; ++i) {
        double_rooms[i] = 10;
    }
    printf("Добро пожаловать на ночную экскурсию в отель.\n");
    printf("Вы задали количество клиентов, ожидающих заселения, равным: %d.\n", MAX_CLIENTS);
    printf("Вы задали количество наблюдателей равным: %d.\n", MAX_OBSERVERS);
    printf("Администратор (сервер) готов заселять клиентов.\n");

    int i = 0; // clients
    int j = 0; // observers
    for (;;) {
	socklen_t clntlen = sizeof(clientaddr);
        int symbols;
	if ((symbols = recvfrom(sockfd, line, 256, 0, (struct sockaddr*) &clientaddr, &clntlen)) < 0) {
	    perror("can't get message");
	    close(sockfd);
	    exit(1);
        }
        line[symbols] = '\0';
        char f = line[0];
        if (f == 'c') {
            // client connection
	    client_sockets[i] = clientaddr;
            printf("Администратор (сервер) обрабатывает клиента %d.\n", i + 1);
            sprintf(observer_message, "Администратор (сервер) обрабатывает клиента %d.\n", i + 1);
            send_observer(observer_message);
            int client_sex = line[1] - '0';
            int place_number = line[2] - '0';
            int room_number_first = line[3] - '0';
            int room_number_second = line[4] - '0';
            int room_number = room_number_first * 10 + room_number_second;
            printf("Администратор (сервер) заселяет клиента в комнату %d.\n", room_number + 1);
            sprintf(observer_message, "Администратор (сервер) заселяет клиента в комнату %d.\n", room_number + 1);
            send_observer(observer_message);
            if (place_number == 1) {
                room_single_add(client_sex, room_number, single_rooms);
            } else {
                room_double_add(client_sex, room_number, double_rooms);
            }
            ++i;
        }
        if (i == MAX_CLIENTS) {
            break;
        }
        if (f == 'o') {
	    observer_sockets[j] = clientaddr;
	    if (j == MAX_OBSERVERS) {
		printf("Слишком много наблюдателей. Администратор стесняется работать...");
       		sprintf(observer_message, "Слишком много наблюдателей. Администратор стесняется работать...");
                send_observer(observer_message);
            	break;
            }
            // observer connection
            printf("К администратору (серверу) подключился наблюдатель %d.\n", j + 1);
            sprintf(observer_message, "К администратору (серверу) подключился наблюдатель %d.\n", j + 1);
            send_observer(observer_message);
            ++j;
        }
    }
    sleep(1);
    printf("А вот и рассвет, экскурсия окончена. Всё, конец!\n");
    sprintf(observer_message, "А вот и рассвет, экскурсия окончена. Всё, конец!\n");
    send_observer(observer_message);
    close(sockfd);
    return 0;
}
