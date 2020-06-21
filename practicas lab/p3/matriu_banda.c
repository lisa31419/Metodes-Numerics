/*RESOL UNA MATRIU DIAGONAL BANDA*/
/*	(b	c	0	0	0)
	(a	b	c	0	0)
	(0	a	b	c	0)
	(0	0	a	b	c)
	(0	0	0	a	b)
n = dimensio, (a,b,c) bandes diagonals vectors de dimensio (n,n+1,n), f = vector solucio inicial del sistema (on es guardaran les noves solucions), tol = tolerancia pel 0*/

int d3(int n, double *a, double *b, double *c, double *f, double tol) {
	/*
	int i;
	for(i = 0; i < n-1; i++) {
		if(fabs(b[i]) < tol) {
			goto stop;
		}
		a[i] = a[i] / b[i];
		b[i+1] = b[i+1] - (a[i] * c[i]);
	}

	double** L = malloc(n * sizeof(double*));
	for(i = 0; i < n; i++) {
		L[i] = malloc(n * sizeof(double));
	}
	double** U = malloc(n * sizeof(double*));
	for(i = 0; i < n; i++) {
		U[i] = malloc(n * sizeof(double));
	}
	for(i = 0; i < n-1; i++) {
		L[i+1][i] = a[i];
		L[i][i] = 1;
		U[i][i] = b[i];
		U[i][i+1] = c[i]; 
	}
	U[n-1][n-1] = b[n-1];
	L[n-1][n-1] = 1;
	resoltriinf(n, L, f, tol);
	resoltrisup(n, U, f, tol);
	return 0;
	stop: return -1;
	*/

	int i;

	c[0] = c[0] / b[0];
	for(i = 1; i < n-1; i++) {
		c[i] = c[i] / (b[i] - (c[i-1] * a[i-1]));
	}

	f[0] = f[0] / b[0];
	for(i = 1; i < n; i++) {
		f[i] = (f[i] - (f[i-1] * a[i-1])) / (b[i] - (c[i-1] * a[i-1]));
	}

	for(i = n-2; i > -1; i--) {
		f[i] = f[i] - (c[i] * f[i+1]);
	}

	return 0;
}
