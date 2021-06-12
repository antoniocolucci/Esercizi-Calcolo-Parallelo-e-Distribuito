#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000000



int main(int argc, char** argv)
{

    long int i, n = N;
    double x, dx, f, sum, pi;

    printf("Numero di intervalli: %ld\n", n);

    sum = 0.0;
    dx = 1.0 / (double)n; //base di ogni rettangolo che serve per calcolare l'integrale.


    #pragma omp parallel for private(x,f,i) shared(dx,sum,n) //creo un team di thread.
    for (i = 1; i <= n; i++)
     {
       x = dx * ((double) (i-0.5));
       f = 4.0 / (1.0 + x*x);

       #pragma omp critical //ogni thread aggiorna la variabile sum, uno alla volta, in modo sequenziale. Senza questo costrutto i thread leggono e modificano sum senza coordinarsi.*/
       sum = sum + f; //ogni thread aggiorna la variabile sum.
     }

     pi = dx*sum;

     printf("PI %.24f\n", pi);

    return 0;
}
