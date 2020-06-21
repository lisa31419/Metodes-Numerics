/*///P8 : APROXIMACIO D'UNA FUNCIO PER SPLINES CUBICS///*/

/*INTERPOLACIO D'UN SEGUIT DE NODES UTILITZANT SPLINES CUBICS*/

/*///ATRIBUTS :
	- n : Nombre de nodes
	- p : Nombre de punts per spline (20) // Punts totals = np + 1
	- delta : Vector x dels nodes
	- y : Vector y dels nodes
*/
void p8_1(int n, int p, double* delta, double* y) {
	int i, j;

	/*Ajustament pel codi*/
	n = n - 1;

	/*Vector d'intervals*/
	double* h = malloc((n) * sizeof(double));
	for(i = 0; i < n; i++) {
		h[i] = delta[i+1] - delta[i];
	}

	/*Vectors pel sistema tridiagonal, m tindra els moments M1 -> Mn-1*/
	double* a = malloc((n-2) * sizeof(double));
	double* b = malloc((n-1) * sizeof(double));
	double* c = malloc((n-2) * sizeof(double));
	double* m = malloc((n-1) * sizeof(double));
	for(i = 0; i < n-2; i++) {
		a[i] = h[i+1] / 6.0;
		b[i] = (h[i] + h[i+1]) / 3.0;
		c[i] = h[i+1] / 6.0;
		m[i] = ((y[i+2] - y[i+1]) / h[i+1]) - ((y[i+1] - y[i]) / h[i]);
	}
	b[n-2] = (h[n-2] + h[n-1]) / 3.0;
	m[n-2] = ((y[n] - y[n-1]) / h[n-1]) - ((y[n-1] - y[n-2]) / h[n-2]);
	d3(n-2, a, b, c, m, 1e-10);

	/*Quan tenim els moments, calculem els Ai i els Bi*/
	double* B = malloc((n) * sizeof(double));
	double* A = malloc((n) * sizeof(double));
	B[0] = y[0];
	A[0] = ((y[1] - y[0]) / h[0]) - (h[0] * m[0] / 6.0);
	for(i = 1; i < n-1; i++) {
		B[i] = y[i] - (m[i-1] * h[i] * h[i] / 6);
		A[i] = ((y[i+1] - y[i]) / h[i]) - (h[i] * (m[i] - m[i-1]) / 6.0);
	}
	B[n-1] = y[n-1] - (m[n-2] * h[n-1] * h[n-1] / 6);
	A[n-1] = ((y[n] - y[n-1]) / h[n-1]) + (h[n-1] * m[n-2] / 6.0);

	/*Passem a l'avaluacio del spline cubic*/
	/*Agafem un nombre de punts i avaluem. El nombre m indica punts per spline cubic*/
	
	double x, eval;
	/*Primer punt*/
	x = delta[0];
	eval = (m[0] * pow(x - delta[0], 3)) / (6.0 * h[0]) + (A[0] * (x - delta[0])) + B[0];
	printf("%25.16lf %25.16lf\n", x, eval);

	/*Primer spline*/
	for(i = 0; i < p; i++) {
		x = delta[0] + ((delta[1] - delta[0]) * (i+1) / (p + 0.0));
		eval = (m[0] * pow(x - delta[0], 3)) / (6.0 * h[0]) + (A[0] * (x - delta[0])) + B[0];
		printf("%25.16lf %25.16lf\n", x, eval);
	}

	/*Segon a penultim spline*/
	for(j = 1; j < n-1; j++) {
		for(i = 0; i < p; i++) {
			x = delta[j] + ((delta[j+1] - delta[j]) * (i+1) / (p + 0.0));
			eval = (((m[j-1] * pow(delta[j+1] - x, 3)) + (m[j] * pow(x - delta[j], 3))) / (6.0 * h[j])) + (A[j] * (x - delta[j])) + B[j];
			
			printf("%25.16lf %25.16lf\n", x, eval);
		}
	}

	/*Ultim spline*/
	for(i = 0; i < p; i++) {
		x = delta[n-1] + ((delta[n] - delta[n-1]) * (i+1) / (p + 0.0));
		eval = (m[n-2] * pow(delta[n] - x, 3)) / (6.0 * h[n-1]) + (A[n-1] * (x - delta[n-1])) + B[n-1];
		printf("%25.16lf %25.16lf\n", x, eval);
	}
}
