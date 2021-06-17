#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

double *matxvet(int m, int n, int *x, double **A);

int main()
{

    int n ,m, i, j, *x;
    double ** mat, *b;


    printf("Inserire il numero di righe della matrice: ");
    scanf("%d", &n);

    printf("Inserire il numero di colonne della matrice: ");
    scanf("%d", &m);

    //Allocazioni dinamiche.
    x = (int *) malloc(m*sizeof(int));
    b = (double *) malloc(n*sizeof(double));
    mat = (double **) malloc(n*sizeof(double *));

    for (i = 0; i < n; i++)
      mat[i]=(double *) malloc(m*sizeof(double *));

    printf("\n");

    for (i = 0; i < m; i++){

         printf("Inserire elemento nel vettore X: \n");
         scanf("%d", &x[i]);
    }

    //Stampa del vettore.
    for (i = 0; i < m; i++){

        printf("Vettore X: %d\n", x[i]);
    }

     srand(time(NULL));
    //Inserimento valori nella matrice.
    for (i = 0; i < n; i++)
      for (j = 0; j < m; j++){

           mat[i][j] = 1 + rand() %10; //Riempimento della matrice con numeri casuali da 1 a 50.
    }


    //Stampa della matrice.
     for (i = 0; i < n; i++){
      for (j = 0; j < m; j++){

           printf("%f\t", mat[i][j]);
    }

     printf("\n");
    }

    printf("\n");

    b = matxvet(m, n, x, mat);

    //Stampa del risultato.
    for (i = 0; i < n; i++){

       printf("Vettore b: %f\n", b[i]);
      }

      free(x);
      free(b);
      free(mat);
}


double *matxvet(int m, int n, int *x, double **A)
{
        int i, j;
        double *b;

        b = (double*)malloc(n*sizeof(double));

        #pragma omp parallel for default(none) shared(m,n,A,x,b) private(i,j)
        for(i = 0; i < n; i++){

            for(j = 0; j < m; j++)

                    b[i] += A[i][j]*x[j];
        }
            return b;
}
