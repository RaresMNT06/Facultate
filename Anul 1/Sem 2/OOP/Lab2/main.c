#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool este_prim(int n) {
    //Verifica daca un numar este prim
    //param: n - numarul intreg
    //pre: n trebuie sa fie un numar intreg (int)
    //post: ret true daca numarul este prim si false in caz contrar


    if (n <2) return false;
    if (n == 2) return true;
    if (n % 2 == 0)return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void genereaza_numere(int n) {
    //Problema 2. Generaza primele n numere prime
    //param: n - numarul de numere prime
    //pre: n trebuie sa fie >=0
    //post: afiseaza in consola primele n numere prime

    if (n<=0) {
        printf("Nu s-au solicitat numere prime");
        return;
    }
    int contor= 0;
    int numar_curent =2;

    printf("Primenele %d numere prime sunt: ", n);
    while(contor < n) {
        if(este_prim(numar_curent)) {
            printf("%d ", numar_curent);
            contor++;
        }
        numar_curent++;
    }
    printf("\n");
}
void calcul_putere(int n, double x) {

    //Problema 12. Calculeaza x^n
    //param: x -> numar real (BAZA); n-> numar nat pozitiv(EXPONENTUL)
    //pre: n trebuie sa fie strict pozitiv
    //post: afiseaza x^n

    double putere=1.0;
    if (n==0) {
        printf("%lf ", putere);
    }
    else{
        putere = pow(x,n);
        printf("%lf", putere);
    }
}

int main() {
    // Functia main
    char optiune;
    int n;
    double x;

    //Meniul
    printf("\n--- MENIU NUMERE PRIME ---");
    printf("\n1. Genereaza primele n numere prime");
    printf("\n2. Determina valoarea lui x^n.");
    printf("\n0. Iesire");
    printf("\nAlegeti optiunea: ");
    scanf_s("%c", &optiune);

    while (optiune != '0'){
        if (optiune=='1') {
            printf("Introduceti n: ");
            scanf_s("%d", &n);

            if (n < 0) {
                printf("Eroare: n trebuie sa fie un numar natural (pozitiv).\n");
            } else {
                genereaza_numere(n);
            }
            printf("\nAlegeti optiunea: ");
            scanf_s("%c", &optiune);
        }
        else if (optiune=='2') {
            printf("Introduceti n(Numar nat): ");
            scanf_s("%d", &n);
            printf("Introduceti x(Numar real): ");
            scanf_s("%lf", &x);
            if (n < 0) {
                printf("Eroare: n trebuie sa fie un numar natural (pozitiv).\n");
            }
            else {
                calcul_putere(n, x);
            }
            printf("\nAlegeti optiunea: ");
            scanf_s("%c", &optiune);
        }
        else if (optiune==0) {
            printf("byebye");
            break;
        }
        else {
            printf("Optiune invalida. Incercati din nou.\n");
            printf("\nAlegeti optiunea: ");
            scanf_s("%c", &optiune);

        }
    }
    return 0;
}