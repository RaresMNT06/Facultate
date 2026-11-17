#include <stdio.h>
#include <string.h>      // memset
#include <stdint.h>      // uint16_t, uint32_t
#include <stdlib.h>
#include <unistd.h>      // close
#include <sys/socket.h>  // socket, connect, send, recv
#include <netinet/in.h>  // struct sockaddr_in, htons
#include <arpa/inet.h>   // inet_addr

int main()
{
    setbuf(stdout, NULL);


    //[Soket]
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


    char sir[1024];
    printf("Introduceti sirul: ");
    fgets(sir, sizeof(sir), stdin);                  // citește tot rândul, cu spații
    sir[strcspn(sir, "\n")] = '\0';                  // scot Enter-ul de la final

    //[send]
    uint16_t n = strlen(sir);
    uint16_t n_retea = ntohs(n);
    send(sd, &n_retea, sizeof(n_retea), 0);
    send(sd, sir, n, 0);


    //[recv]
    uint16_t spatii;
    recv(sd, &spatii, sizeof(spatii), MSG_WAITALL);
    spatii = ntohs(spatii);
    printf("Nr de spatii %hu\n", spatii);

    close(sd);
    return 0;



}