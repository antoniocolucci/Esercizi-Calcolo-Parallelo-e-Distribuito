#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int n_threads, id_thread, i;


     //omp_set_num_threads(5); //setto il numero di thread.


    /*#pragma omp parallel private (id_thread) //i 3 thread faranno contemporaneamente quello che c'è all'interno delle parentesi graffe
    {
      id_thread = omp_get_thread_num();
      printf ("Sono: %d \n", id_thread);

      #pragma omp for //i 3 thread si organizzeranno e si distribuiranno le operazioni.

        for (i = 0; i <= 4; i++)
        {
          printf ("Iterazione %d del thread %d. \n", i, id_thread);
        }

    }*/

    //I costrutti Parallel e For possono anche essere combinati. Il numero di threads può essere settato nella diretta con num_threads.
    #pragma omp parallel for private(id_thread) num_threads(5)
    for(i = 0; i < 5; i++)
     {
      id_thread = omp_get_thread_num();
      printf ("Iterazione %d del thread %d. \n", i, id_thread);
     }


    return 0;
}
