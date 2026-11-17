#include <stdio.h>
#include <string.h>      // memset
#include <stdint.h>      // uint16_t, uint32_t
#include <unistd.h>      // close
#include <sys/socket.h>  // socket, bind, listen, accept, send, recv
#include <netinet/in.h>  // struct sockaddr_in, htons, INADDR_ANY
#include <arpa/inet.h>   // inet_ntoa

int main()
{
    setbuf(stdout,NULL); //pentru ce printf urile sa apara in consola


    //[Soket]
    int sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd < 0)
    {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //[bind]
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = INADDR_ANY;
    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind");
        return 1;
    }

    //[listen]
    listen(sd, 5);


    while (1)
    {
        //[accept]
        struct sockaddr_in client;
        socklen_t len = sizeof(client);

        printf("Waiting for connection...\n");
        int c = accept(sd, (struct sockaddr *)&client, &len);
        if (c < 0)
        {
            perror("accept");
            continue;
        }

        printf("S a conectat %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        //[recv]

        uint16_t n;
        recv(c, &n, sizeof(uint16_t), MSG_WAITALL);
        n = ntohs(n);

        char sir[1000];
        memset(sir, 0, sizeof(sir));
        if (n >= sizeof(sir))
            n = sizeof(sir)-1;
        recv(c, sir, n, MSG_WAITALL);
        printf("Am primit: \"%s\" (%hu caractere)\n", sir, n);

        uint16_t nr_car = 0;
        for (int i = 0; i < n; i++)
        {
            if (sir[i] == ' ')
                nr_car++;
        }
        printf("Spatii = %hu\n", nr_car);

        nr_car = htons(nr_car);
        send(c, &nr_car, sizeof(nr_car), 0);

        close(c);
    }
}