#include <stdio.h>
#include <string.h>

int lungime(int len, int l, char cuvant[]);

int medie(int len_cuvinte[], int med, int n);


int main()
{
    int n,l,med= 0;
    scanf("%d", &n);
    scanf("%d", &l);  // lungime de verificare 
    char cuvant[100];
    int len_cuvinte[50];
    
    for(int i=0;i<n;i++){
        scanf("%s", &cuvant);
        int len= strlen(cuvant);
        lungime(len, l, cuvant);
        med= med+len;
        len_cuvinte[i] = len;
    
    
    
    }
    med/=n;
    
    printf("%d", medie(len_cuvinte, med,n));
    
    
    
    
    return 0;
}