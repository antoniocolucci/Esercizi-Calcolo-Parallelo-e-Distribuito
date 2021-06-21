/*Se in input viene dato un numero di numeri (N) non divisibile per il numero di threads(t),
  allora è necessario effettuare una modifica.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    int N, i, t, nloc, r, id, step;
    float sumtot, sum, *a, t0, t1, t_tot;

    sumtot = 0;

    printf("Inserire la dimensione del vettore: ");
    scanf("%d", &N);

    a = (float*)calloc(N,sizeof(float)); //array allocato dinamicamente.

    printf("Inserire i numeri da sommare: \n");
    for(i = 0; i < N; i++)
    {
       scanf("%f", &a[i]);
    }

    t0 = omp_get_wtime();

    #pragma omp parallel private(sum, nloc, i, id, step) shared(sumtot, r)
    {
        t = omp_get_num_threads();
        nloc = N/t; //Divisione tra il size del vettore e il numero di threads.


        r = N%t; //Resto
        id = omp_get_thread_num(); //Recupero l'id del thread.


        if (id < r)
        {
           nloc++;
           step = 0;
        }
        else
           step = r; //La variabile step consente ad ogni core di sapere di quali elementi si deve occupare.


        printf("Sono il thread con id %d, di %d: numeri %d, resto = %d, step = %d\n",id,t,nloc,r,step);

        sum = 0;

        for(i = 0; i < nloc; i++)
        {
            sum = sum+a[i+nloc*omp_get_thread_num()+step];
        }

        printf("Sono il thread con id %d, di %d: numeri %d, resto = %d, sum = %f\n",id,t,nloc,r,sum);
        sumtot+=sum;
        t1 = omp_get_wtime();
    }

    printf("\nLa somma totale e': %f\n", sumtot);

    t_tot = t1-t0;

    printf ("\nTempo totale: %f \n", t_tot);

}
