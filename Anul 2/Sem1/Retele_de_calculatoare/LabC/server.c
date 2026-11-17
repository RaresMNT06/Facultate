#include <stdio.h>
#include <string.h>      // memset
#include <stdint.h>      // uint16_t, uint32_t
#include <unistd.h>      // close
#include <sys/socket.h>  // socket, bind, listen, accept, send, recv
#include <netinet/in.h>  // struct sockaddr_in, htons, INADDR_ANY
#include <arpa/inet.h>   // inet_ntoa

int main(){
    setbuf(stdout,NULL); //pentru ce printf urile sa apara in consola

    // [SOKET]
    int sd  = socket(AF_INET, SOCK_STREAM, 0); // „vreau un telefon IPv4, TCP”

    if (sd<0){
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //[BIND]
    struct sockaddr_in server;                                      // iau un formular de adresă
    memset(&server, 0, sizeof(server));                       // îl șterg
    server.sin_family = AF_INET;                                    // tip: IPv4
    server.sin_port = htons(1234);                         // apartament: 1234
    server.sin_addr.s_addr = INADDR_ANY;                            // bloc: orice IP al meu
    if (bind(sd, (struct sockaddr*)&server, sizeof(server)) < 0)   // leg telefonul de adresă
    {
        perror("bind");
        return 1;
    }

    //[LISTEN]
    listen(sd, 5);

    //[ACCEPT]
    while (1)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);

        printf("Serverul asteapta clienti ... \n");
        int c = accept(sd, (struct sockaddr*)&client, &len);
        if (c<0)
        {
            perror("accept");
            continue;
        }
        printf("S-a conectat %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        //[RECV]
        uint16_t n;
        recv(c, &n, sizeof(uint16_t), MSG_WAITALL);
        n = ntohs(n);

        uint32_t suma = 0;
        for (int i = 0; i < n; i++)
        {
            uint16_t x;
            recv(c, &x, sizeof(x), MSG_WAITALL);
            x = ntohs(x);
            printf("  am primit %hu\n", x);
            suma += x;
        }

        suma = htonl(suma);         //trimit suma
        send(c, &suma, sizeof(suma), 0);

        close(c);
    }

}