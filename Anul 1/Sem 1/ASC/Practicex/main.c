#include<stdio.h>

int special(int n, int nr,int nr_cif);

int determinare(int len, int v);

int main()
{
   int n,v[100],i=0,len=0,nr,nr_cif=0;
   
   scanf("%d", &n);
   while(scanf("%d", &nr)){
       int temp=nr;
       nr_cif=0;
       while(temp!=0){
            temp= temp/10;
            nr_cif++;
       }
       if(special(n, nr, nr_cif)==1)
       {    
            v[len] = nr;
            len++;
       }
   }
        for(i=0;i<len;i++)
           printf("%d ", v[i]);
    
    determinare(len , v)
    
       
           
       
       
   
   //int suma = determinare(v);
   return 0;
    
}




