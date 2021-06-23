#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main()
{

    int n, i, token, t = 2, result, *a;

    printf("Inserire la dimensione del vettore: ");
    scanf("%d", &n);

    a = (int *)malloc(n*sizeof(int));

    for(i = 0; i < n; i++)
    {
        a[i] = 2 * i;
        printf("[%d]\t", a[i]);
    }

    printf("\nInserire il numero da cercare: ");
    scanf("%d", &token);


    result = binarySearch(0, n - 1, t, token, a);

    if (result < 0)
        printf("\nThe number not is in the vector.");
    else
        printf("\nThe number is in the position: %d\n", result+1);


    return 0;
}



int binarySearch(int left, int right, int t, int token, int *a)
{
    int result = -1, i;

    int size = (right - left + 1)/2; //Sottoporzione del vettore.

    if (size == 0)  //Se il vettore è composto da un solo elemento.
    {
      if(a[left] != token) //Se l'unico elemento presente nel vettore è diverso dalla chiave, ritorna -1.
        {
            return -1;
        }
      else
         {
            return left; //Se l'unico elemento presente nel vettore è uguale alla chiave, ritorna la posizione in cui si trova l'elemento.
         }
    }

    omp_set_num_threads(t); //t = 2, quindi 2 thread.
    omp_set_nested(1);

    #pragma omp parallel shared(a, token, left, right, size, result)
    {
        int id = omp_get_thread_num();

        int leftThread = left + id * size;
        int rightThread = leftThread + size - 1;

        printf("\nLeftThread: %d", leftThread);
        printf("\nRightThread: %d", rightThread);

        if(id == t-1)
            rightThread = right; //7

        if(a[leftThread] <= token && a[rightThread] >= token)
        {
            result = binarySearch(leftThread, rightThread, t, token, a);
        }
    }
}
