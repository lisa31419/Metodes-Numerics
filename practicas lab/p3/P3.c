
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* FUNCIONES */
void dif_div(int, double*, double*);
double hornerNew(int, double*, double*, double);
void funcio (int, double, double);
void funcio_q (int, double, double);


int main (void){
    /* Variables */
    int i;
    int n = 17;
    double a = -4,b = 4;

    
    for(i = 0; i <= n; i++){
        printf("\n -> Iteracio %d\n: ", i);
        funcio (i, a, b);
        if(i%2 == 0){
            funcio_q(i,a,b);
        }
        
    }
    funcio(2.6, a,b); 
    funcio_q(2.6,a,b);
    
    return 0;
     
}

/* Funcio funcio
 *  Evalua la funció de funcio per a una abscissa determinada
 * - Atributs: 
 *    · Nombre d'iteracions n
 *    · Intervalo [a,b]
 */
void funcio (int n, double a, double b){
    /* Variables */
    int i;
    /*double valor_fun, valor_pol_horner;*/
    
    /* Demanem la memoria dinamica */
    double *x1 = malloc ((n+1) * sizeof(double));
    double *y = malloc ((n+1) * sizeof(double));
    double *y2= malloc ((n+1) * sizeof(double));
    
    /* Funcio on avaluarem  */
    double funcion(double x){
        return sinh(x) * cos(3*x);
    }
    
    /* Inicialitzem els vectors */
    for (i = 0; i <= n; i++){
        x1[i] = a + (i* (b-a) / (n));
        y[i] = funcion(x1[i]);
        
    }
    
    dif_div(n, x1, y);
    
    
    printf("Els coeficientes del Pol Interpolador amb diferencies dividides son:\n");
    for(i = 0; i <= n; i++){
        printf("%le\t", y[i]);
    }
    
    printf("\n");
    
    for (i = 0; i <= n; i++){
        if(i > 0){
            y2[i] = y[i]*(x1[i] - x1[0]) + y[i-1];
        } else{
            y2[i] = y[i];
        }     
    }
    
    printf("\n");
    
    printf("Els coeficientes sense x[0]:\n");
    for(i = 0; i <= n; i++){
        printf("%le\t", y2[i]);
    }
    
    printf("\n");
    

    free(x1);
    free(y);
    free(y2);

}


void funcio_q (int n, double a, double b){
    int k;
    double *x2 = malloc ((n+1) * sizeof(double));
    double *q = malloc ((n+1) * sizeof(double));
    
    /* Funcio on avaluarem  */
    double funcion(double x){
        return sinh(x) * cos(3*x);
    }
    
    
    for (k = 0; k <= n; k++){
        x2[k] = a + (k* (b-a) / (n));
        q[k] = funcion(x2[k]);
           
    }
    
    dif_div(n, x2, q);
    
    printf("\n");
    
    printf("Els coeficientes de q[x] son:\n");
    for(k = 0; k <= n; k++ ){
        printf("%le\t", q[k]);    
        
    }
    
    printf("\n");
    printf("\n");
    
    free(x2);
    free(q);
    
}

/* Funcio dif_div 
 * Donats els vectors x i f, omple el vector f amb les
diferencies dividides 
 - Atributs: 
    -> Grau n
    -> Vectors x i f
*/
void dif_div(int n, double* x, double* f){
    int i, j;
    
    for(j = 1 ; j <= n; j++){
        for(i = n; i >= j; i--){
            f[i] = (f[i] - f[i-1])/(x[i]-x[i-j]);
        }
    }
}

/* Funcio hornerNew
 * Donats els vectors x i f, avalua el polinomi interpolador en el punt z, usant la regla de Horner.
 - Atributs: 
    -> Grau n
    -> Vectors x i f
    -> Punt z
*/
double hornerNew(int n, double *x, double *b, double z){
    int i;
    double valor = b[n];
    
    for(i = n-1; i >= 0; i--){
        valor = valor*(z-x[i]) +b[i];
    }
    
    return valor;
}

