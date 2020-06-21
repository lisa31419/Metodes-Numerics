/*///P7 : APROXIMACIO D'UNA FUNCIO PER NEWTON (DIFERENCIES DIVIDIDES)///*/

/* n = largada dels vectors x, f; x, f = vectors amb els punts a interpolar */
void difdiv(int n, double* x, double* f) {
	int i, j;
	for(i = 1; i < n; i++) {
		for(j = n-1; j > i-1; j--) {
			f[j] = (f[j] - f[j-1]) / (x[j] - x[j-i]);
		}
	}
}

/* z = valor en que avaluar el polinomi; n = llargada del vector de coeficients; x, c = vectors amb els coeficients i els valors de les x */
/* Forma del polinomi : c0 + c1(x-x0) + c2(x-x0)(x-x1) + ... */
double horner(double z, int n, double* x, double* c) {
	int i;
	double r = c[n-1];
	for(i = n-2; i > -1; i--) {
		r = r * (z - x[i]);
		r = r + c[i];
	}
	return r;
}

/*INTERPOLACIO D'UN SEGUIT DE NODES UTILITZANT DIFERENCIES DIVIDIDES*/
/*///ATRIBUTS :
	- n : Nombre de nodes
	- m : Nombre de punts (100)
	- x : Vector x dels nodes
	- f : Vector y dels nodes
*/
void p7_1(int n, int m, double* x, double* f) {
	int i;

	difdiv(n, x, f);

	double* xp = malloc((n-1) * sizeof(double));
	for(i = 0; i < n-1; i++) {
		xp[i] = x[i];
	}

	printf("Punts del polinomi : \n");
	for(i = 0; i < m; i++) {
		double xi = x[0] + ((x[n-1] - x[0])*(i/(m - 1.0))); 
		double eval = horner(xi, n, xp, f);
		printf("%25.16lf %25.16lf\n", xi, eval);
	}
}
