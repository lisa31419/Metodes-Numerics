/*INTERPOLACIO D'UNA FUNCIO EN [a,b] UTILITZANT SPLINES CUBICS*/
/*///ATRIBUTS : (CAL CANVIAR FEVAL // DEFECTE FABS)
	- n : Nombre de nodes
	- p : Nombre de punts per spline (20) // Punts totals = np + 1
	- (a,b) : Interval d'interpolacio
*/
void p8_2(int n, int p, double a, double b) {
	int i;

	double feval(double x) {
		return fabs(x);
	}

	/*Creem els nodes a interpolar*/
	double* delta = malloc(n * sizeof(double));
	double* y = malloc(n * sizeof(double));
	for(i = 0; i < n; i++) {
		delta[i] = a + ((b-a)*i/(n-1.0));
		y[i] = feval(delta[i]); /*Part de la funcio a interpolar*/
	}
    /*splines_cubics.c*/
	p8_1(n, p, delta, y);
}
