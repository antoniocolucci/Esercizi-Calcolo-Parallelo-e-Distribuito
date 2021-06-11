#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{


    int id_thread, num_thread;

    #pragma omp parallel private(id_thread) shared(num_thread) //creo un team di thread.
    {
      id_thread = omp_get_thread_num();
      num_thread = omp_get_num_threads();

      printf("Hello World from thread %d, nthread %d\n", id_thread, num_thread);

    }

//Per variare il numero dei core digitare nel terminale: export OMP_NUM_THREADS=2 (esempio con 2 threads).
//Per verificare il tempo di esecuzione del programma utilizzare il comando time: time./hello.

    return 0;
}
