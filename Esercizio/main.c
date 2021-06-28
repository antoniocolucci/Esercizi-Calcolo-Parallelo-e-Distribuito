#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{

    int **mat, *x, n, m, i, j, p = 4, sumtot = 0, sum;

    printf("Inserire numero righe matrice: ");
    scanf("%d", &n);

    printf("Inserire numero colonne matrice: ");
    scanf("%d", &m);

    mat = (int **)malloc((n*n)*sizeof(int *));
    x = (int *)malloc(n*sizeof(int ));

    for(i = 0; i < n; i++)
    mat[i] = (int *)malloc(m*sizeof(int *));


    printf("\nInserire elementi nella matrice: \n");

    for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){
        scanf("%d", &mat[i][j]);

    }
    }

    //Stampa della matrice.
    printf("\nMatrice: \n");
    for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){

         printf("%d\t", mat[i][j]);
      }
      printf("\n");
    }

    #pragma omp parallel for private (i, j, sum) shared(n, m, x, mat) num_threads(p) reduction (+: sumtot)
     for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){

        if(i == j)
        {
          x[i] = mat[i][j];
        }
      }
    }

    printf("\n");

    printf("Vettore x: ");

    for(i = 0; i < n; i++)
    {
      printf("%d\t", x[i]);
    }

    sum = 0;

    for(i = 0; i < p; i++)
    {
      sum = sum + x[i+p*omp_get_thread_num()];
    }

    sumtot+=sum;

    printf("\nLa somma e' : %d\n", sumtot);



    return 0;
}
