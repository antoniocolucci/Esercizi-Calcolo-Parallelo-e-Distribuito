/*Se in input viene dato un numero di numeri (N) non divisibile per il numero di threads(t),
  allora è necessario effettuare una modifica.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int N, i, t, nloc, r, id, step; //La variabile step
    float sumtot, sum, *a;

    sumtot = 0;

    printf("Inserire N: ");
    scanf("%d", &N);

    a = (float*)calloc(N,sizeof(float)); //array allocato dinamicamente.

    printf("Inserire i numeri da sommare: \n");
    for(i = 0; i < N; i++)
    {
       scanf("%f", &a[i]);
    }

    #pragma omp parallel private(sum, nloc, i, id, step) shared(sumtot, r)
    {
        t = omp_get_num_threads();
        nloc = N/t;

        printf("Sono il thread %d, di %d: numeri %d\n", omp_get_thread_num(), t, nloc);

        r = N%t; //resto
        id = omp_get_thread_num(); //recupero l'id del thread.

        printf("Sono il thread con id %d, di %d: numeri %d, resto =% d\n",id,t,nloc,r);


        if (id < r)
        {
           nloc++;
           step = 0;
        }
        else
           step = r;


        printf("Sono il thread con id %d, di %d: numeri %d, resto = %d, step = %d\n",id,t,nloc,r,step);

        sum = 0;

        for(i = 0; i < nloc; i++)
        {
            sum = sum+a[i+nloc*omp_get_thread_num()+step];
        }

        printf("Sono il thread con id %d, di %d: numeri %d, resto = %d, sum = %f\n",id,t,nloc,r,sum);
        sumtot+=sum;
    }

    printf("La somma totale e': %f\n", sumtot);


}
