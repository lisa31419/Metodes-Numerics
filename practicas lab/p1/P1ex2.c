#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float redondear(float f);


int main (void){
    // Variables
	int n;
	double I, Ired, error;
	
    // Integral I
	I = 0.5 * log((double)9/7);
	
	Ired = redondear(I);
	error = I - Ired;
	 
	// Pedimos por teclado el número de iteraciones
	printf("-> Número de iteraciones: ");
	scanf("%d", &n);
	
	// Imprimimos por pantalla el error
	printf("\n · ERROR:\nI = %le \n· Para n = 0 tenemos: \n", I);
	printf("\n -> I - Ired =  %le\n", fabs(I - Ired));
    printf("----------------------------------------------------\n");
	
	for(int i = 1; i < n; i++){
    	I = 0.5 * ((1 / i) - (7 * I));
    	Ired = 0.5 * ( (1 / i) - (7 * Ired));
    	
    	error = 0.5 * (7 * (-error));
        
        printf("i = %d \t\t %le \n", i,  I - error);
	}


return 0;

}

// Funcón para redondear
float redondear(float f){
	f *= 1000000;
    float flo;
	flo = (int) f;

	if(f - flo >= 0.5){
	    flo++;
	}
	
	flo *= 0.000001;

    return flo;
}

// El error es inestable, ya que, como muestran los datos, este oscila y se hace mayor con cada iteración








