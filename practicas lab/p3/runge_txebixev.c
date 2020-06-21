/*INTERPOLACIO D'UNA FUNCIO PER ABCISSES DE CHEBISHEV UTILITZANT DIFERENCIES DIVIDIDES*/

/*///ATRIBUTS : 
(CAL CANVIAR FEVAL // INTERPOLA DE -1 A 1 // DEFECTE RUNGE)
	- n : Nombre de nodes (30)
	- m : Nombre de punts (120)
	- [a,b] : Interval d'extrapolacio
*/

void p7_2cheb(int n, int m, double a, double b) {
	int i;

	double feval(double x) {
		return 1.0 / (1.0 + (25.0 * pow(x, 2)));
	}

	double* x = malloc(n * sizeof(double));
	double* y = malloc(n * sizeof(double));
	for(i = 0; i < n; i++) {
		x[i] = a + ((b-a) / 2 * (1 + cos(M_PI * ((2*(n-i)) - 1) / (2*n))));
		y[i] = feval(x[i]);
	}

	difdiv(n, x, y);

	double* xp = malloc((n-1) * sizeof(double));
	for(i = 0; i < n-1; i++) {
		xp[i] = x[i];
	}

	printf("Punts del polinomi : \n");
	for(i = 0; i < m; i++) {
		double xi = x[0] + (i * (x[n-1] - x[0]) / (m - 1.0)); 
		double eval = horner(xi, n, xp, y);
		printf("%25.16lf %25.16lf\n", xi, eval);
	}
}
