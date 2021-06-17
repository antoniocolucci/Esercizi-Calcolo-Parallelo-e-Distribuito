#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>


int main(int argc, char* argv[])
{

    int i,j, N, M, alfa, beta, t, ops = 0;
    double *A, *b , *a , *R, p = 0.00f, t0, t1, tempotot;

      if(argc > 1)
      {
         t = atoi(argv[1]); //Numero di thread. Recupero la stringa digitata nel terminale e la trasformo in intero.
         M = atoi(argv[2]);
         N = atoi(argv[3]);
         alfa = atoi(argv[4]);
         beta = atoi(argv[5]);
      }
      else
      {
         printf("Error usage : ./ exec <nThreads> <M> <N> <alpha> <beta>\n") ;
         exit(EXIT_FAILURE) ;
      }

      //Controllo divisibilità.
      if((M%2)!= 0)
      {
        printf("Il secondo parametro (M = numero di righe) deve essere un numero pari.\n");
        exit(EXIT_FAILURE);
      }

      //Allocazioni dinamiche.
      A = (double *)malloc((M*N)*sizeof(double)); //Matrice allocata come vettore.
      b = (double *)malloc(N*sizeof(double));
      a = (double *)malloc(M*sizeof(double));
      R = (double *)malloc(M*sizeof(double));

      //Generazione di valori pseudo-casuali.
      for (i = 0; i < M; i++)
      {
            a[i] = (double) ((rand()%1000)+1)/1000; //Genero il vettore "a" con numeri casuali da 1 a 999. Divido per 1000 in modo di poter considerare i numeri da 1 a 9.

            for(j = 0; j < N; j++){
            A[(i*N)+j] = (double) ((rand()%1000)+1)/1000; //Riempimento della matrice "A" con numeri casuali da 1 a 9. Con i*N mi colloco nella riga desiderata, +j mi posiziono sulla colonna.
            printf("%f\t", A[i]);

            }
            printf("\n");
      }

      for(i = 0; i < N; i++)
      {
        b[i] = (double) ((rand()%1000)+1)/1000; //Genero il vettore b.
        t0 = omp_get_wtime();
      }

      #pragma omp parallel for schedule(static) shared(N, M, A, b, a, alfa, beta, ops) private(i, j) num_threads(t)
      for (i = 0; i < M; i++)
      {
        for (j = 0; j < N; j++)
        {
           R[i] += alfa*A[(i*N)+j]*b[j];
           #pragma omp critical //Imposto un lock di accesso a questa regione di istruzioni che deve essere eseguita in mutua esclusione.
           {
             ops = ops + 1;
           }
        }

        R[i] += (a[i]*beta);
      }

      #pragma omp parallel for shared (R,M,a) private(i) reduction(*: p) num_threads(t)
      for (i = 0; i < M; i++)
           p*=R[i];

      t1 = omp_get_wtime();
      tempotot = t1 - t0;

      printf("Elapsed time: %lfs \nOps: %d \n", tempotot, ops);
      free(A);
      free(b);
      free(a);
      free(R);

      exit(EXIT_SUCCESS);

}
