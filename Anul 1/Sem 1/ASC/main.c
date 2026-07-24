#include <stdio.h>

/// static int cmd/ val 0

void testALL() {

}

typedef struct {
    int div[100];
    int cate;

}MyList;

MyList divizori(int nr) {
    MyList rez;
    rez.cate = 0;
    for (int i = 1; i <= nr; i++) {
        if (nr % i == 0) {
            rez.div[(rez.cate)++]=i;
        }
    }
    return rez;
}
int run() {
    while (1) {
        printf("1 Divizori\n0 Iesire\nDati comanda:");
        char cmd;
        scanf("%c", &cmd);
        if (cmd == '0') {
            break;;
        }
        if (cmd == '1') {
            //divizori
            int nr;
            scanf_s("%d", &nr);
            //TODO
            MyList div = divizori(nr);
            for (int i = 0; i < div.cate; i++) {
                printf("%d \n", div.div[i]);
            }
        }
        else {
            printf("Comanda invalida\n");
        }
    }
    return 0;
}
int main() {

    run();
    return 0;
}