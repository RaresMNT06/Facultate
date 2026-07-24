#include <stdio.h>
#include <string.h>

void citiresir(char sir[])
{
    scanf("%[^\n]", sir);
}
int numara(char cuvant[]);

int main()
{
    char sir[101];
    citiresir(sir);
    
    char* p=strtok(sir, " ");
    while(p)
    {
        int valoare = numara(p);
        printf("%d ", valoare);
        p = strtok(NULL, " ");
        
    }
    
    return 0;
}