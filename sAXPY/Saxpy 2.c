#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{

    int *A, *a, *b, *R;
    int m, n, i, j, alfa, beta, t, p = 1;

    printf("Inserire numero righe matrice: ");
    scanf("%d", &n);

    printf("Inserire numero colonne matrice: ");
    scanf("%d", &m);

    printf("Inserire alfa: ");
    scanf("%d", &alfa);

    printf("Inserire beta: ");
    scanf("%d", &beta);

    printf("Inserire numero thread: ");
    scanf("%d", &t);

    A = (int *)malloc((n*m)*sizeof(int));
    a = (int *)malloc(n*sizeof(int));
    b = (int *)malloc(m*sizeof(int));
    R = (int *)malloc(m*sizeof(int));


    if(n%t != 0)
    {
      printf("\nIl numero di righe deve essere divisibile per il numero di thread.\n");
      exit(EXIT_FAILURE);
    }


    srand(time(NULL));
    printf("\nVettore b: \n");
    for(i = 0; i < m; i++)
    {
      b[i] = 1+rand()%10;
      printf("%d\t", b[i]);
    }

    printf("\nVettore a: \n");
    for(i = 0; i < n; i++)
    {
      a[i] = 1+rand()%10;
      printf("%d\t", a[i]);
    }

    printf("\nMatrice A: \n");
    for(i = 0; i < n; i++)
    {
     for(j = 0; j < m; j++)
     {
       A[(i*m)+j] = 1+rand()%10;
       //A[i] = 1 + rand() % 10;
       printf("%d\t", A[i]);
     }
     printf("\n");
    }

    printf("\nRisultato: ");
    #pragma omp parallel for shared(n, m, A, a, b, R, alfa, beta) private(i, j) num_threads(t)
    for(i = 0; i < n; i++)
    {
      for(j = 0; j < m; j++)
      {
        R[i] += A[(i*m)+j]*b[j]*alfa;
      }
      R[i] += beta*a[i];
    }

    #pragma omp parallel for shared(n, R) private(i) num_threads(t) reduction(*:p)
    for(i = 0; i < n; i++)
    {
      p*=R[i];
      printf("%d", p);
    }

   free(A);
   free(R);
   free(a);
   free(b);

   return 0;
}
