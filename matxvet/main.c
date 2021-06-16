#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

double *matxvet(int m, int n, int *x, double **A);

int main()
{

    int n ,m, i, j;

    double ** mat;
    double *b;
    int *x;


    printf("Inserire il numero di righe della matrice: ");
    scanf("%d", &n);

    printf("Inserire il numero di colonne della matrice: ");
    scanf("%d", &m);

    x = (int *) malloc(n*sizeof(int));
    b = (double *) malloc(n*sizeof(double));

    mat = (double **) malloc(n*sizeof(double *));

    for (i = 0; i < n; i++)
      mat[i]=(double *) malloc(m*sizeof(double *));

    printf("\n");

    for (i = 0; i < n; i++){

         printf("Inserisci elemento nel vettore X: \n");
         scanf("%d", &x[i]);
    }

    //Stampa del vettore.
    for (i = 0; i < n; i++){

        printf("Vettore X: %d\n", x[i]);
    }


    //Inserimento valori nella matrice.
    for (i = 0; i < n; i++)
      for (j = 0; j < m; j++){

           printf("Inserisci elemento di riga %d e colonna %d: \n", i, j);
           scanf("%lf", &mat[i][j]);
    }


    //Stampa della matrice.
     for (i = 0; i < n; i++){
      for (j = 0; j < m; j++){

           printf("%f\t", mat[i][j]);

    }

    printf("\n");
    }

    printf("\n");

    b = matxvet(n, m, x, mat);

    //Stampa del risultato.
    for (i = 0; i < n; i++){

       printf("Vettore b: %f\n", b[i]);

      }


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
