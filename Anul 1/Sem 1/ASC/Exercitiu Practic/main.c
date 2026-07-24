#include <stdio.h>
#include <string.h>

char *prelucrare(char cuvant[], int len);

//int citire(int n);


int main()
{
    int n;
    scanf("%d", &n);
    
    char cuvant[31];
    char *vector[101];
    
    for(int i=0;i<n;i++)
    {
        scanf("%s", cuvant);
        int len = strlen(cuvant);
        vector[i] = prelucrare(cuvant, len);     
        
        
    }
     for(int i=0;i<n;i++)
         printf("%s ", vector[i]);
     
    

    //citire(n);
    
    return 0;
    
    
    
    
}