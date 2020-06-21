#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* FUNCIONES */
double funtion(double);
double funtion2(double);
double derFuntion2(double);

double trapezis(double, double, int, double (*)(double));
double Simpson(double, double, int, double (*)(double));
double richardson(double, double, double, int, int, double (*)(double));

int newton (double, int, double *, double, double, double (*)(double), double (*)(double));
void print_newton(int, double);

double f1_integral_valor =  -0.1437553801251907;

int main(void){
    /* VARIABLES */
    int n = 1, len = 30;
    int iteraciones_max, resultado_newton;
    double a = 0.5, b = 1.0;
    double tol = 1e-6, tol2 = 1e-8;
    double valor_integral, error, x0, solution, result;
    
    
    
    /*--------------------------------------
     *-------------- TRAPEZIS --------------
     *--------------------------------------
     */

    /* Calculamos la función trapezis y el error para la función 1 */
    valor_integral = trapezis(a, b, n, funtion);
    error = fabs(valor_integral - f1_integral_valor);
    
    /* Mientras el error sea mayor que la tolerancia */
    
    while(error > tol){
        n += 1;
        
        valor_integral = trapezis(a, b, n, funtion);
        
        error = fabs(valor_integral - f1_integral_valor);
        printf("---------------------------------------------------------------------------------------\n");
        printf("\n\n-> Resultado de Trapezis para la función: ");
        printf("\n\t· Valor de n: %d \n\t· Valor del error: %16.10lf \n\t· Valor de la integral: %16.10lf \n\n", n, error, valor_integral);
        printf("---------------------------------------------------------------------------------------\n");
            
    }
    
    /* Reestablecemos el valor de n para usarla con la función */
    n = 1;
    
     /*--------------------------------------
     *-------------- RICHARDSON --------------
     *--------------------------------------
     */
     
    /* Calcularemos Richardson para la función */
    
    result = richardson(a,b,tol,n,len,funtion);
    printf("-> El resultado final de Richardson para la función es %16.10lf ", result);
    printf("\n\n-------------------------------------------------------------\n");
    printf("-------------------------------------------------------------\n\n");
    
    
     /*--------------------------------------
     *-------------- SIMPSON --------------
     *--------------------------------------
     */
    
     /* Reestablecemos n a 1 para usarla en Simpson */
    n = 1;

    /* Calculamos la función de Simpson y el error para la función */
    valor_integral = Simpson(a, b, n, funtion);
    error = fabs(valor_integral - f1_integral_valor);
    
    /* Mientras el error sea mayor que la tolerancia */
    while(error > tol){
        n += 1;
        
        valor_integral = Simpson(a, b, n, funtion);
        
        error = fabs(valor_integral - f1_integral_valor);
        
        printf("-----------------------------------------------------------------------------------");
        printf("\n\n-> Resultado de Simpson para la función: ");
        printf("\n\t· Valor de n: %d \n\t· Valor del error: %16.10lf \n\t· Valor de la integral es: %16.10lf \n\n", n, error, valor_integral);
        printf("-----------------------------------------------------------------------------------\n");
    }
    
     /*--------------------------------------
     *-------------- NEWTON --------------
     *--------------------------------------
     */
     
     /* Reestablecemos a y b para usarlos en Newton */
     a = -1.0;
     b = 2.0;
     
    
    printf("\nIntroduzca el valor de x0:");
    scanf("%le", &x0);
    
    printf("\nIntroduzca el numero de iteraciones maximas:");
    scanf("%d", &iteraciones_max);
    
    
    resultado_newton = newton(x0, iteraciones_max, &solution, tol, tol2, funtion2, derFuntion2);
    printf("\n\nFunción 2:");
    print_newton(resultado_newton, solution);
    
    
    return 0;
}




/* FUNCIONES */


/* funtion:
 *   - Función que calcula, según una x dada, la función 
 *   - Return: double resultante
*/
double funtion(double x){
    return (sinh((2.0*x)/3.0)*cos(5.0*x));
}

/* funtion2:
 *   - Función que calcula, según una x dada, la función del ejercicio 2
 *   - Return: double resultante
*/
double funtion2(double x){
    return (pow(x,2.0) - 2.0*x*exp(-x) + exp(-2.0*x));
}


/* derFuntion:
 *   - Función que calcula la derivada de la función dada una x
 *   - Return: double resultante
*/
double derFuntion2(double x){
    return (2.0*x - 2.0*exp(-x) + 2.0*x*exp(-x) - 2.0*exp(-2.0*x));
}

/* trapezis:
 *   - Función que calcula la fórmula de los trapecios en un 
 *     intervalo [a,b] para un número n de iteraciones
 *   - Return: double T_h resultante 
 */
double trapezis(double a, double b, int n, double(* funtion)()){
    /* VARIABLES */
    int i;
    double h, T_h;
    
    /* Calculamos el valor de h para Trapezis */
    h = (double)((b-a)/((double)n));
    
    /* Calculamos la fórmula Trapezis en [a,b] 
     * mientras i sea menor a n y con xi = a + ih 
     */
    
    /* Valor de Trapezis en i = 0 */
    T_h = (funtion(a)/(2.0));
    
    for(i = 1; i < n ; i++){  
        T_h += funtion(a + i*h);
    }
    
    /* Valor de Trapezis en i = n */
    T_h += (funtion(b)/(2.0));
    
    T_h *= h;
    
    return T_h;
}



/* Simpson:
 *   - Función que calcula la fórmula de Simpson en un 
 *     intervalo [a,b] para un número 2n de iteraciones
 *   - Return: double S_h resultante 
 */
double Simpson(double a, double b, int n, double(* funtion)()){
    /* VARIABLES */
    int k;
    double h, S_h;
    
    /* Calculamos el valor de h para Simpson */
    h = (double)((b-a)/((double)2*n));
    
    
    /* Calculamos la fórmula de Simpson en [a,b] 
     * mientras k sea menor a 2n y con xk = a + kh 
     */
    
    /* Valor de Simpson en k = 0 */
    S_h = funtion(a);
    
    for(k = 1; k < 2*n; k++){
        if(k % 2 == 0){
            /* f par */
            S_h += 2.0*funtion(a + k*h);
        } else {
            /* f impar */
            S_h += 4.0*funtion(a + k*h);
        }
        
    }
    /* Valor de Simpson en k = n */
    S_h += funtion(b);
    
    S_h *= (h/3.0);
    
    return S_h;
    
}



/* richardson
 *    - Función que calcula la extrapolación de Richardson
 *      en un intervalo [a,b] bajo una tolerancia
 *    - Return: último valor de Richardson
 */
double richardson(double a, double b, double tol, int n, int len, double(* funtion)()){
    /* VARIABLES */
    int i,j;
    double resultado;
    double *valores_rich = malloc( len * sizeof(double));
    
    printf("----------------------------------------------------\n");
    printf(" iteración \t\t valores de Richarson \n");
    printf("----------------------------------------------------\n");
    
    /* Calculamos la función f(h) a partir de las anteriores */
    for( j = 0; j < len; j++){
        /* Imprimimos la columna en la que estamos trabajando*/
        printf("\t j = %d \n", j); 
        printf("----------------------------------------------------\n");
        for(i = j; i < len; i++){
            
            if(j == 0){
                /* Si es la primera columna*/
                valores_rich[i] = trapezis(a,b,n,funtion); 
                n *= 2;
            } else {
                /* Para el resto de columnas */
                valores_rich[i] +=  ((valores_rich[i]- valores_rich[i-1])/(pow(2,2*j)-1));
                
            }
            printf(" i = %d \t\t %16.10le \n",i, valores_rich[i]);
            
        }
            
        /* Si los 2 valores son muy proximos entre si paramos el proceso*/
        if(fabs(valores_rich[j+1] - valores_rich[j]) < tol){
            resultado = valores_rich[j];
            free(valores_rich);
            return resultado;
        }
        printf("----------------------------------------------------\n");
    }

    resultado = valores_rich[len-1];
    free(valores_rich);
    return resultado;
    
}


/* newton:
 *    - Función que devuelve:
 *      -> 0 si la función converge antes de alcanzar el número de iteraciones máximas
 *      -> 1 si se supera el número de iteraciones máximas
 *      -> 2 si la derivada es 0 
 */
int newton (double x0, int it_max, double * sol, double tol1, double tol2, double(* funtion)(), double(* funtion_der)()){
    /* VARIABLES */
    int iteraciones = 0;
    int contador = 0;
    double derivada, valor_funtion, valor_anterior;
    *sol = x0;
    
    /* Establecemos como valor anterior la x0 y calculamos el valor de x1*/
    valor_anterior = x0;

    derivada = funtion_der(*sol);
    valor_funtion = funtion(*sol);
    
    *sol -= (valor_funtion/derivada);
    
    /* Mientras no se alcancen 1 o los 2 criterios de parada de Newton-Raphson */
    while( fabs(funtion(*sol)) > tol1 || fabs(valor_anterior - *sol) > tol2){
        /* -> if: Si se alcanza el número de iteraciones máximas
         * -> else if: Si la derivada es 0
         */
        contador += 1;
        if(iteraciones >= it_max){
            return 1;
        } else if(funtion_der(*sol) == 0){
            return 2;
        }
        
        /* Calculamos el siguiente valor */
        valor_anterior = *sol;

        derivada = funtion_der(*sol);
        valor_funtion = funtion(*sol);
        
        *sol -= (valor_funtion/derivada);
        
        iteraciones += 1;
        
        /*
        printf("\n· Valor anterior de la función: %16.8le \n· Valor actual de la función: %16.8le\n", valor_anterior, *sol);
        */
        
    }
    
    /* Imprimirems por pantalla el numero de iteraciones totales */
    printf("\n\n->  El número de iteraciones realizadas es: %d\n\n", contador);
    
    return 0;
    
}

/* print_newton:
 *    - Función que imprime el resultado de Newton-Raphson
 *      según el int que retorne la función de Newton
 */
void print_newton(int resultado, double sol){
    if(resultado == 0){
        printf(" ha habido convergencia y la solución es: %16.10le \n", sol);
        
    } else if(resultado == 1){
        printf(" se ha alcanzado el número máximo de iteraciones sin tener la tolerancia pedida. \nSolución parcial obtenida: %16.10le \n", sol);
        
    } else{
        printf(" el valor de la derivada es 0.\n");
    }
    
}




