#include <stdio.h>

int main(){

    int n;
    double x, s=0;
    printf("Introduceti numarul de numere:\n");
    scanf_s("%d",&n);
    for (int i=1;i<=n;i++)

    {   printf("Introduceti numarul:\n");
        scanf_s("%lf",&x);
        s+=x;
    }
    printf("Suma este: %.2lf\n", s);

    return 0;



}