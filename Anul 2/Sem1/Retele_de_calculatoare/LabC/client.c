#include <stdio.h>
#include <string.h>      // memset
#include <stdint.h>      // uint16_t, uint32_t
#include <stdlib.h>
#include <unistd.h>      // close
#include <sys/socket.h>  // socket, connect, send, recv
#include <netinet/in.h>  // struct sockaddr_in, htons
#include <arpa/inet.h>   // inet_addr

int main(){
    setbuf(stdout, NULL);

    //[SOKET]
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        perror("socket");
        return 1;
    }

    //[connect]
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sd, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("connect");
        return 1;
    }

    //[SEND]
    uint16_t n;
    scanf("%hu", &n);

    uint16_t n_retea = ntohs(n);
    send(sd, &n_retea, sizeof(uint16_t), 0); // trimit n

    for (int i=0; i<n; i++)
    {
        uint16_t x;
        scanf("%hu", &x);
        x = htons(x);
        send(sd, &x, sizeof(x), 0); // trimit fiecare nr
    }

    //[RECV]
    uint32_t suma;
    recv(sd, &suma, sizeof(suma), MSG_WAITALL);
    suma = ntohl(suma);
    printf("Suma: %u\n", suma);

    close(sd);
    return 0;
}