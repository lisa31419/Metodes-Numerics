
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float fun_skf(float k);
double fun_sk(double k);

int main(void){
   
    int i=4, n;
    double arrel2 = sqrt(2);
    double pi = 2*4*atan(1);
   
    // Pedimos por teclado el número de vértices
    printf("· Número de vértices: \n"); 
    scanf("%d", &n);
    printf("---------------------------------------------------------------------");
  
    // Imprimimos por pantalla los vértices, la aproximación y el error relativo
    printf("\nVÉRTICES \tAPROXIMACIÓN \t\t  ERROR RELATIVO \n");
    printf("  %d  \t %22.15e  \t %22.15e\n", i, i*arrel2, (pi-i*arrel2)/pi);
    printf("---------------------------------------------------------------------");
    
    // Para la función sk
    printf("\n -> Función sk: \n");
    
    // Precisión simple
    printf("\n  - Precisión simple\n");
    
    for(int j = 0; j < n; j++){ 
        i *= 2;
        arrel2 = fun_skf(arrel2);    
        printf("  %d  \t %22.15e \t %22.15e\n", i, i*arrel2, (pi - i*arrel2)/pi);   
            
    }
    
    // Precisión doble
    printf("\n - Precisión doble\n");
    
    i = 4;
	arrel2 = sqrt(2);
	
    for(int j = 0; j < n; j++){ 
        i *= 2;
        arrel2 = fun_sk(arrel2);    
        printf("  %d  \t %22.15e \t %22.15e\n", i, i*arrel2, (pi - i*arrel2)/pi);   
            
    }

    printf("---------------------------------------------------------------------");

	i = 4;
	arrel2 = sqrt(2);
	
	// Función ck:
	
	printf("\n -> Función ck: \n");
	
	// Precisión simple
	printf("\n - Precisión simple\n");
	for (int j = 0; j < n; j++){
        i *= 2;
        arrel2 = fun_skf(arrel2); 
    	arrel2 = (2*arrel2) / sqrt(4 - (arrel2*arrel2));   
        printf("  %d  \t %22.15e  \t %22.15e\n", i, i*arrel2, (pi - i*arrel2)/pi);   
            
    }
    
	// Precisión doble
	printf("\n - Precisión doble\n");
	i = 4;
	arrel2 = sqrt(2);
	
	for (int j = 0; j < n; j++){
        i *= 2;
        arrel2 = fun_sk(arrel2); 
    	arrel2 = (2*arrel2) / sqrt(4 - (arrel2*arrel2));   
        printf("  %d  \t %22.15e  \t %22.15e\n", i, i*arrel2, (pi - i*arrel2)/pi);   
            
    }
   
   printf("---------------------------------------------------------------------");

return 0;

}

// Función para calcular sk con precisión doble
double fun_sk(double k){
    double sk;
    sk = sqrt(2 - sqrt(4- (k*k)));
    
    return sk;
}

// Función para calcular sk con precisión simple
float fun_skf(float k){
    float sk;
    sk =  sqrt(2 - sqrt(4- (k*k)));
    
    return sk;
}
