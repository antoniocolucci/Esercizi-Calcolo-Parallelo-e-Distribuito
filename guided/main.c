#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

int main()
{
    int i;



    #pragma omp parallel for private(i) num_threads(5) schedule(guided)
    for(i = 0; i < N; i++)
    {
        sleep(i);
        printf("Il thread %d ha completato iterazione %d.\n", omp_get_thread_num() , i);
    }

    printf("Tutti i thread hanno terminato! \n");

    return 0;
}
