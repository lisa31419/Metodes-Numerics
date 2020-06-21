
/* Fichero: triang.c */

/* ls
 Android Baixades Escriptori
 ... cd Escriptori
 ... gcc -c -ansi -Wall P1ej1.c
 ... gcc P1ej1.o -o ex1.exe -lm
 ... ./ex1.exe 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void) {
    int n, i, j, tipus;
    double **matA; *b;
    
    printf("\nNumero de ecuaciones: ");
    scanf("%d", &n);
    
    matA = (double **) malloc (n * sizeof (double *));
    if (matA == NULL) {
        printf("No hi ha prou memoria\n");
        exit(1);
    }
    
    for(i = 0; i < n; i++) {
        matA[i] = (double *) malloc (n * sizeof (double));
        if (matA[i] == NULL ) {
            printf("No hi ha prou memoria\n");
            exit(2);
        }
    }
    
    b = (double *) malloc (n * sizeof (double));
    x = (double *) malloc (n * sizeof (double));
    if (b == NULL || x == NULL) {
        printf("No hi ha prou memoria\n");
        exit(3);
    }
    
    printf("\n¿Que tipo de matriz triangular quieres?\n");
    printf("\n\n · 0: triangular superior\n\n");
    printf("\n\n · 1: triangular inferior\n\n");
    printf("\n\n · -1: triangular inferior con 1 en la diagonal\n\n");
    
    scanf("%d", &tipus);
    
    triang(n,matA,b,tipus);
    
 return 0;
}


/* Función para resolver un sistema triangular */
/* usando memoria dinamica con variables:
    - n : dimensión del sistema
    - matA : matriz
    - b : termino indeendiente
    - tipus : tipo de sistema triangular(0== sup.; 1== inf.) 
*/
void triang(int n, double **matA, double *b, int tipus) {

    switch(tipus){
        case 0:
            triansup(n, &matA, &b);
            break;
        case 1:
            trianinf(n, &matA, &b);
            break;
        case -1:
            trianinfUnos(n, &matA, &b);
            break;
        default:
            printf("\nCaso incorrecto.\n");
            break;
    }
}    


/* Funcion para resolver un sistema triangular superior */
/* usando memoria dinamica con variables:
    - n: numero de ecuaciones
    - a: matriz
    - b: termino independiente 
*/
int triansup(int n, double **a, double *b) {
    int i, j, k;
    double sum;
    
    printf("\nMatriz del sistema: \n");
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("a(%d, %d): ", i+1, j+1);
            scanf("%lf", &a[i][j]);
        }
    }
    
    printf("\n\nTerminos independientes:\n");
    for(i = 0; i < n; i++) {
        printf("b(%d): ", i+1);
        scanf("%lf", &b[i]);
    }
    for(i = n-1; i >= 0; i--) {
        sum = 0.0;
        for(k = i+1; k < n; k++) 
            sum += a[i][k] * x[k];
        x[i] = (b[i] - sum) / a[i][i];
        
    }
    
    printf("\nEl vector solucion es:\n");
    for(i = 0; i < n; i++) {
        printf("x(%d) = %lf\n", i, x[i]);
    }
    printf("\n");
    for(i = 0; i < n; i++) {
        free (a[i]);
    }
    free (a);
    free (b);
    free (x);
    return 0;

}
