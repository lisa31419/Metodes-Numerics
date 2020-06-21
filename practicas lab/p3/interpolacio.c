/*ANTONIO TIGRI*/
/*Pràctica 3 - Mètodes Numèrics*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* FUNCIONES */

double horner(int, double*, double);
void interpolador(int, double*, double*, double*);

void triang(int, double**, double*, int);
int lu(double**, int, int*, double);
int resolsist(int, int, double**, double**, double);

void crear_matriu(int, int, double**);
void crear_vector(int, double*);

void print_matriu(int, int, double**);
void print_vector(int, double*);
void print_intvector(int, int*);

int mostramenu();
int mostrasubmenu();
int mostrainterpols();
void personalmain();

void controlmenu(int, int, double*, double*, double*);
void controlsubmenu1(int, int, double*, double*, double*);
void controlsubmenu2(int, int, double*, double*, double*);
void controlinterpol(int, int, double*, double*, double*);



int main(void) {
	personalmain();
	return 0;
}

/*-------------------------MÈTODES DE LA PRÀCTICA-----------------------------------------------*/

/* HORNER
 * - Avalua el polinomi interpolador en un punt z a partir de la regla de Horner
 * - Return: double final
 */

double horner(int n, double * a, double z) {
	int i;
	double final = 0.0;
	for (i = n; i > 0; i--) {
		final = (final + a[i]) * z;
	} 
	final += a[0];
	return final;
}



/*INTERPOLADOR
 * - Calcula els coeficients del polinomi interpolador de Lagrange
 */

void interpolador(int n, double * x, double * f, double * a) {
	int i, j, perms;
	int * perm;
	double prod, tol = 0;
	double ** sist;
	
	/*Allocs del sistema*/
	sist = (double**)malloc((n+1)*sizeof(double*));
	perm = (int*)malloc((n+1)*sizeof(int));
	if (sist == NULL || perm == NULL) {
			printf("No hi ha prou memoria\n");
			exit(1);
		}
	for (i = 0; i <= n; i++) {
		sist[i] = (double *)malloc((n+1)*sizeof(double));
		if (sist[i] == NULL) {
			printf("No hi ha prou memoria\n");
			exit(1);
		}
	} /*EOF Allocs*/
	
	printf("Valors de x:\n");
	printvec(n+1, x);
	
	printf("Valors de f:\n");
	printvec(n+1, f);
	
	for (i = 0; i <= n; i++) {
		prod = 1.0;
		for (j = 0; j <= n; j++) {
			sist[i][j] = prod;
			prod = prod*x[i];
		}
	}
	
	for (i = 0; i <= n; i++) {
		perm[i] = i;
	}
	
	perms = lu(sist, n+1, perm, tol); 
	
	printf("Vector de permutacions:\n");
	for (i = 0; i <= n; i++) {
		printf("%d	", perm[i]);
	} printf("\n");
	
	for (i = 0; i <= n; i++) {
		a[perm[i]] = f[i];
	}
	
	printf("Permutacions realitzades: %d", perms);
	
	triang(n+1, sist, a, -1);
	triang(n+1, sist, a, 1);
	
	printf("Coeficients del polinomi interpolador:\n");
	printvec(n+1, a);
	
	for (i = 0; i <= n; i++) {
		free(sist[i]);
	} free(sist);
	free(perm);
}
/*END*/


/*---------------------------MÈTODES DE PRÀCTIQUES ANTERIORS-------------------------------------------------------------*/

/* Función que resuelve un sistema no singular de dimensión n con una matriz matA
 * y termino independiente b. Según el tipus resolverá:
 *    - tipus 0: triangular inferior
 *    - tipus 1: triangular superior
 *    - tipus -1: triangular inferior con 1's en la diagonal
*/

void triang(int n, double **matA, double *b, int tipus) {
	/* VARIABLES */
    int i, j, k;
    double sum;
	
	/* TRIANGULAR INFERIOR */
    if (tipus == 0) {
        for (i = 0; i < n; i++) {
			sum = 0.0;
			for (j = 0; j < i; j++) {
				sum += matA[i][j]*b[j];
			}
			b[i] = (b[i] - sum)/matA[i][i];
		}
    }
    
	/* TRIANGULAR SUPERIOR */
    else if (tipus == 1) {
        b[n-1] = b[n-1] / matA[n-1][n-1];
        
        for (i = n-1; i >= 0; i--) {
			sum = 0.0;
			for (j = i+1; j < n; j++){
				sum += matA[i][j]*b[j];
			}
			
			b[i] = (b[i] - sum)/matA[i][i];
		}
        
    }
    
    /* TRIANGULAR INFERIOR 1's */
    else if (tipus == -1) {
        for (i = 0; i < n; i++) {
			sum = 0.0;
            
			for (j = 0; j < i; j++) {
				sum += matA[i][j]*b[j];
			}
			
			b[i] -= sum;
		}
    }
    
    else {
        printf("Error en les dades introduides\n");
    }
	printf("\n");
}




/* LU:
 * Función que calcula la factorización PA = LU de una matriz A nxn
 * usando eliminación gaussiana con pivotaje maximal por columnas.
 * - Return: número de permutaciones
*/
int lu(double** a, int n, int* perm, double tol) {
	
	/* VARIABLES */
    int i, j, k, perm_aux, posmax, perm_counter = 0;
	double aux, pivot;
    double * temp;
	
    for (i = 0; i < n-1; i++) {
		aux = fabs(a[i][i]);
		posmax = i;
        
		for(j = i+1; j < n; j++) {
			if (aux < fabs(a[j][i])) {
				aux = fabs(a[j][i]);
				posmax = j;
			}
		}
		
		if (posmax != i) {
            
			temp = a[i];
			a[i] = a[posmax];
			a[posmax] = temp;
            
            temp = b[i];
            b[i] = b[posmax];
            b[posmax] = temp;
            
			perm_aux = perm[posmax];
			perm[posmax] = perm[i];
			perm[i] = perm_aux;
            
			perm_counter++;
            
		}
		
		if (fabs(a[i][i]) <= tol) {
			return -1;
		} 
		
		else {
			pivot = a[i][i];
			for (j = i+1; j < n; j++) {
				a[j][i] = a[j][i]/pivot;
				for (k = i+1; k < n; k++) {
					a[j][k] = a[j][k] - a[j][i]*a[i][k];
				}
			}
		}
	}
	
	return perm_counter;
    
}



/* RESOLSISTEMA
 * Resol un sistema d'equacions amb matriu de termes independents
 */

int resolsist(int n, int m, double ** a, double ** b, double tol) {
	/* VARIABLES */ 
    int i, j;
    int * perm; 
    double * aux;
    
	perm = (int*) malloc (n*sizeof(int));
	aux = (double*)malloc(n*sizeof(double));
    
    if (perm == NULL || aux == NULL) {
        printf("No hi ha prou memoria\n");
        exit(1);
    }
    
	for (i = 0; i < n; i++) {
		perm[i] = i;
	}
	
	printf("\n-------------------------------\n\n");
    
	printf("-> Matriu del sistema: \n");
	printmatrix(n, n, a);
    
	printf("-> Matriu de termes independents: \n");
	printmatrix(n, m, b);
    
    /* Calculem la descomposicio LU */
	int perms = lu(a, n, perm, tol);
    
	printf("Descomposició LU:\n");
	printmatrix(n, n, a);
    
	printf("Matriu de permutacions:\n");
	for (i = 0; i < n; i++) {
		printf("\n");
        
		for (j = 0; i < n; j++) {
			if (j == perm[j]) {
				printf("%d	", perm[i]);
			}
			else {
				printf("0  ");
			}
			
		} 
		printf("\n\n");
        
	}
	
	for (j = 0; j < m; j++) {
		for (i = 0; i < n; i++) {
			aux[perm[i]] = b[i][j];
		} 
		/* Calculem triang */
		triang(n, a, aux, -1);
        triang(n, a, aux, 1);
        
		for (i = 0; i < n; i++) {
			b[i][j] = aux[i];
		}
		
	}
	printf("-> Matriu de solucions: \n");
    printmatrix(n, m, b);
        
	free(perm);
	free(aux);
    
	printf("\n-------------------------------\n\n");
	return perms;
}


/*---------------------MÈTODES UTILS------------------------------------------*/

/* CREAMATRIX 
 * Assigna valors a una matriu amb memaria dinamica pero buida
 */

void crear_matriu(int n, int m, double ** a) {
	int i, j; 
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			printf("[%d][%d] = ", i, j);
			scanf("%lf",&a[i][j]);
		} printf("\n");
	}	
}
/*END*/


/*CREAVECTOR - Assigna valors a un vector*/
/*START*/
void creavec(int n, double * v) {
	int i; 
	for (i = 0; i < n; i++) {
		printf("[%d] = ", i);
		scanf("%lf",&v[i]);
	}
}
/*END*/


/*PRINTMATRIX - Imprimeix una matriu*/
/*START*/
void printmatrix(int n, int m, double ** a) {
	int i, j; printf("Imprimint Matriu:\n");
	for (i = 0; i < n; i++) {
		printf("\n");
		for (j = 0; j < m; j++) {
			printf("%10.4e	", a[i][j]);
		} printf("\n\n");
	}
}
/*END*/


/*PRINTVECTOR - Imprimeix un vector*/
/*START*/
void printvec(int n, double * v) {
	int i; printf("Imprimint Vector:\n\n");
	for (i = 0; i < n; i++) {
		printf("%10.4e	", v[i]);
	} printf("\n\n");
}
/*END*/


/*PRINTINTVECTOR - Imprimeix un vector d'enters*/
/*START*/
void printintvec(int n, int * v) {
	int i; printf("Imprimint Vector:\n\n");
	for (i = 0; i < n; i++) {
		printf("%d	", v[i]);
	} printf("\n\n");
}
/*END*/


/*--------------------MÈTODES PERSONALS DE GESTIÓ-----------------------------------------------------------------------*/

/*MOSTRAMENU - Imprimeix les diferents operacions que es poden realitzar i demana una d'elles*/
/*START*/
int mostramenu() {
	int option;
	printf("\n-------------------------------\n\n");
	printf("0: Sortir\n");
	printf("1: Establir valors dels vectors\n");
	printf("2: Mostrar informacio\n");
	printf("3: Trobar polinomi interpolador\n"); 
	printf("4: Verificar validesa del polinomi interpolador\n");
	printf("5: Provar Horner amb el polinomi interpolador actual i un valor qualsevol\n");
	printf("\nOpcio escollida: ");
	scanf("%d",&option);
	return option;
}



/*MOSTRASUBMENU 
 * Imprimeix els diferents tipus de vectors sobre els que es pot actuar
 * Return: int opcio
 */

int mostrasubmenu() {
	int option;
	printf("\n-------------------------------\n\n");
    printf("Opcions a escollir: \n");
	printf("\t[0] Tornar enrere\n");
	printf("\t[1] Vector x\n");
	printf("\t[2] Vector f\n");
	printf("\t[3] Polinomi Interpolador\n");
	printf("\t[4] Tots\n"); 
    
	printf("\n-> Opcio: ");
	scanf("%d",&option); printf("\n");
    
	return option;
    
}



/*MOSTRAINTERPOL 
 * Imprimeix les opcions per calcular el polinomi interpolador
 */

int mostrainterpols() {
	int option;
	printf("\n-------------------------------\n\n");
    printf("Opcions a ecollir: \n");
	printf("\t[0] Tornar enrere\n");
	printf("\t[1] Metode amb sitema\n");
    
	printf("\n-> Opcio: ");
	scanf("%d",&option); 
    printf("\n");
    
	return option;
    
}



/*PERSONALMAIN 
 * Main personal que utilitzo per fer totes les proves mitjançant un menu*/

void personalmain() {
	int opcio = 1, n;
	double * x, * f, * a;
	
	printf("\n-> Grau del polinomi: ");
	scanf("%d", &n);
	while (n < 0) {
		printf("\nEntrada invalida, utilitza un nombre natural.\n");
		printf("\n-> Grau del polinomi: ");
		scanf("%d", &n);
	}
	
	x = (double*) malloc ((n+1)*sizeof(double));
	f = (double*) malloc ((n+1)*sizeof(double));
	a = (double*) malloc ((n+1)*sizeof(double));
    
	if (x == NULL || f == NULL || a == NULL) {
		printf("No hi ha prou memoria\n");
		exit(1);
	}
	
	while (opcio != 0) {
		opcio = mostramenu();
		controlmenu(opcio, n, x, f, a);
	}
	
	free(x);
	free(f);
	free(a);
	
	printf("Vols continuar amb un altre grau (n)? [1 = SI] [resta = NO]: ");
	scanf("%d", &opcio); 
    printf("\n-------------------------------\n\n");
	if (opcio == 1) {
		personalmain();
	}
	
}



/*CONTROLMENU - Controla les diferents opcions del menú*/

void controlmenu(int opcio, int n, double * x, double * f, double * a) {
	int i, subopcio = 1;
	double punt;
	bool trobat = true;
	switch(opcio) {
		case 0: {
			printf("Sortint.\n\n");
            
			break;
		}
		case 1: {
			while (subopcio != 0) {
				subopcio = mostrasubmenu();
				controlsubmenu1(subopcio, n, x, f, a);
			}
			
			break;
		}
		case 2: {
			while (subopcio != 0) {
				subopcio = mostrasubmenu();
				controlsubmenu2(subopcio, n, x, f, a);
			}
			
			break;
		}
		case 3: {
			subopcio = 1;
			while (subopcio != 0) {
				subopcio = mostrainterpols();
				controlinterpol(subopcio, n, x, f, a);
			}
			
			break;
		}
		case 4: {
			for (i = 0; i <= n && trobat; i++) {
				if (horner(n, a, x[i]) != f[i]) {
					trobat = false;
				}
			}
			if (trobat) {
				printf("\nEl polinomi interpolador es correcte\n");
			}
			else {
				printf("\nEl polinomi interpolador es incorrecte.\n");
			}
			
			break;
		}
		case 5: {
			printf("\n-> Punt on vols estudiar el polinomi interpolador amb Horner: ");
			scanf("%lf", &punt); 
            
            printf("\n");
            /* Calculem horner */
			punt = horner(n, a, punt);
			printf("f(p) = %.4e\n", punt);
            
			break;
		}
		default: {
			printf("\nEntrada invalida\n");
            
			break;
		}
		
	}
	
}


/*CONTROLSUBMENU 1 - Controla el menu 1 de selecció de vector*/
void controlsubmenu1(int opcio, int n, double * x, double * f, double * a) {
	switch(opcio) {
		case 0: {
			printf("Tornant enrere...\n");
			break;
		}
		case 1: {
			printf("-> Defineix x: \n");
			crear_vector(n+1, x);
            
			break;
		}
		case 2: {
			printf("-> Defineix f: \n");
			crear_vector(n+1, f);
            
			break;
		}
		case 3: {
			printf("-> Defineix el polinomi interpolador: \n");
			crear_vector(n+1, a);
            
			break;
		}
		case 4: {
			printf("-> Defineix x: \n");
			crear_vector(n+1, x);
            
			printf("-> Defineix f: \n");
			crear_vector(n+1, f);
            
			printf("-> Defineix el polinomi interpolador: \n");
            
			crear_vector(n+1, a);
            
			break;
		}
		default: {
			printf("Entrada invalida\n");
            
			break;
		}
	}
}


/*CONTROLSUBMENU 2 - Controla el menu 2 de selecció de vector*/
/*START*/
void controlsubmenu2(int opcio, int n, double * x, double * f, double * a) {
	switch(opcio) {
		case 0: {
			printf("Tornant enrere...\n");
            
			break;
		}
		case 1: {
			printf("Mostrant x:\n");
			print_vector(n+1, x);
            
			break;
		}
		case 2: {
			printf("-> Mostrant f: \n");
			print_vector(n+1, f);
            
			break;
		}
		case 3: {
			printf("-> Mostrant polinomi interpolador: \n");
			print_vetor(n+1, a);
            
			break;
		}
		case 4: {
			printf("-> Mostrant x: \n");
			print_vector(n+1, x);
            
			printf("-> Mostrant f: \n");
			print_vector(n+1, f);
            
			printf("-> Mostrant polinomi interpolador: \n");
			print_vector(n+1, a);
            
			break;
		}
		default: {
			printf("\nEntrada invalida.\n");
            
			break;
		}
	}
}
/*END*/


/*CONTROLINTERPOL - Controla el menu de interpolacions*/
/*START*/
void controlinterpol(int opcio, int n, double * x, double * f, double * a) {
	switch(opcio) {
		case 0: {
			printf("Tornant enrere...\n");
			break;
		}
		case 1: {
			interpolador(n, x, f, a);
			break;
		}
		default: {
			printf("\nEntrada invalida\n");
			break;
		}
	}
}
/*END*/



/*-----------------------------------------------------------------COSES PER FER CTRL C CTRL V-----------------------------------------------------------------------------------------*/

/*ALLOCATIONS D'UN VECTOR (double i int)*/
/*START*/
/*
vecint = (int*)malloc(tam*sizeof(int));
vecdouble = (double*)malloc(tam*sizeof(double));
if (vecdouble == NULL || vecint == NULL) {
	printf("No hi ha prou memoria\n");
	exit(1);
}
*/
/*END*/

/*ALLOCATIONS D'UNA MATRIU (double)*/
/*START*/
/*
matriu = (double**)malloc(files*sizeof(double*));
if (matriu == NULL) {
	printf("No hi ha prou memoria\n");
	exit(1);
for (i = 0; i < files; i++) {
		b[i] = (double*)malloc(columnes*sizeof(double));
		if (b[i] == NULL) {
			printf("No hi ha prou memoria\n");
			exit(1);
		}
	}
*/
/*END*/
