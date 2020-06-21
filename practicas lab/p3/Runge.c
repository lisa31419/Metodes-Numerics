#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#define N 21
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862

/*main: llegir n (grau pol. interpol)*/
/*llegir a, b ( a<b)*/
/*llegim un indicador per crear els nodes*/
/*nodes (indic, n, a, b, *x) es generen els nodes (diferents entre si) per equiespaiats, Txebixev, aleatòries*/
/*omplir *f amb f(xi)'s*/
/*difdiv(n, *x, *f)*/
/*Per a "molts" z pertany a (a,b) equidistants   z, f(z), f'(z), p(z), p'(z) */
/*Fer horner*/
void hornerd(int, double, double*, double*, double);
void nodes (n, a, b, *x);
void f( n, a, b, *x, *f);
void difdiv (int n, double *x, double *f);

int main (void){
	int n, a, b;
	double x[N - 1], f[N - 1], p[N - 1], dev[2], dpol[2];
	FILE *ex;
	
	srand(time(NULL));
	
	printf("Digues el grau màxim del polinomi si us plau.\n");
	scanf("%d", &n);
	n++;
	
	if(n > 20 || n < 0) return 1;

	printf("Ara, digues l'interval d'interpolarització, si us plau.\n");
	do{
		scanf("%d%d", &a, &b);
	}while(a > b);
	
	nodes(n, a, b, x);
	f(n, a, b, x, f);
	
	/*Calculem el polinomi interpolador*/
	for(i = 0; i < n; i++)
		p[i] = f[i];

	difdiv (n, x, p);

	ex = fopen("sol.res","w");
	if(ex == NULL){
		printf("Error de fichero\n");
		exit(1);
	}
	
	for( i = 1; i <= n; i++){
		z = a + i * (2/n);
		hornerd( n, z, x, f, dev);
		hornerd( n, z, x, p, dpol);
		fprintf(ex, "%le\t%le\t%le\t%le\t%le\n", z, dev[0], dev[1], dpol[0], dpol[1]);
	}

	fclose(ex);

	return 0;
}
	
	
	
void hornerd( int n, double z, double *x, double *f, double p[2]){
	int i;

	p[0] = f[n];
	p[1] = 0;
	
	for(i = n - 1; i >= 0; i--){
		p[1] = p[1]*(z-x[i])+p[0]; 
		p[0] = p[0]*(z-x[i])+f[i];
	}
}


void nodes (n, a, b, *x){
	int indicador;
	
	printf("De quina manera vols crear els nodes:\n\t1) Equiespaiats\n\t2) Txebixev\n\t3) Aleatòriament\n");
	scanf("%d", &indicador);
	
	switch (indicador){
		case 1 : 
			printf("Equiespaiats\n");
			x[0] = (b-a)/n;
			for(i=0; i < n; i++)
				x[i] = x[i-1] + ((b-a)/n);

		case 2: 
			printf("Txebitxev\n");
			for(i=0;i<=n;i++)
				x[i]=((b-a)/2)*(cos(((2*i+1)*PI)/(2*(n+1))) +1)+a;

		case 3: 
			printf("Aleatòriament\n");
			/*Donara nombres entre a i b*/
			srand(time(NULL));
			for( i = 0; i < n; i++)
				x[i]=(b-a)*rand()/RAND_MAX + a;
				for(j = i - 1; j >= 0; j--)
					if(fabs( x[i] - x[j] ) <= 1e-4){
						printf("Puntos iguales\n");
						exit(1);
					}

	}

	/*Escrivim els nodes*/
	printf("Els nodes són:\n");
	for(i = 0; i < n; i++)
		printf("%x[%d]:\t%le\n", i, x[i]);

}

void f( n, a, b, *x, *f){
	int ind;

	printf("Quina funció vols utilitzar?\n1: f(x) = 1/(1 + 25 *x^2)\n2: cos x\n");
	scanf("%d", &ind);

	switch (ind){
		case 1: 
			printf("1/(1 + 25 *x^2)\n");
			for (i = 0; i < n; i++)
				f[i] = 1/(1 + 25 * pow( x[i], 2));

		case 2: 
			printf("cos x\n");
			for (i = 0; i < n; i++)
				f[i] = cos ( x[i] );

	}

	/*Escrivim els valors dels nodes*/
	printf("Els valors dels nodes són:\n");
	for(i = 0; i < n; i++)
		printf("%f[%d]:\t%le\n", x[i], f[i]);
}

/*Calculem el polinomi interpolador pel mètode de diferències dividides*/
void difdiv (int n, double *x, double *f){
	int i, j; 
	
	for(j = 1; j<=n; j++){
		for( i = n; i>=j; i--){
			f[i] = (f[i] -f[i-1])/(x[i]-x[i-j]);
		}
	}
}

