#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void oddEvenSort (int *a, int N);

int main()
{

    int N, i;

    printf("Inserire il numero degli elementi del vettore da ordinare: ");
    scanf("%d", &N);

    int *a = (int *)malloc(N*sizeof(int));

    for(i = 0; i < N; i++)
    {
      printf("Inserire elemento [%d] nel vettore: ", i);
      scanf("%d", &a[i]);
    }

   oddEvenSort(a,N);

   printf("\nVettore ordinato: ");

   for(i = 0; i < N; i++)
   {
     printf("%d\t", a[i]);
   }


    return 0;
}


void oddEvenSort (int *a, int N)
{

    int sw1 = 1, start = 0, i;
    int temp;


    while(sw1 || start)
    {
      sw1 = 0;

      #pragma omp parallel for private(temp)
        for(i = start; i < N - 1; i += 2) //Ciclo for sugli elementi di indice pari.
        {
          if(a[i] > a[i+1])
          {
            temp = a[i];
            a[i] = a[i+1];
            a[i+1] = temp;
            sw1 = 1;
          }
        }

        if(start == 0)
        {
          start = 1;
        } else
          start = 0;

     }
}
