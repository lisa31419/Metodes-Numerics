/*///P6 : APROXIMACIO D'UNA FUNCIO PER NEWTON (PUNTS)///*/

/*APROXIMACIO D'UNA FUNCIO PER LA RESOLUCIO D'UN SISTEMA D'EQUACIONS DIFERENCIALS*/

/*///ATRIBUTS :
	- (a,b) : Interval d'interpolacio
	- alfa : f(a)
	- beta : f(b)
	- n : Nombre de punts (100)
	- prec : Precisio dels calculs (1e-10)
	- kmax : Iteracions maximes (10)
*/

void p6(double a, double b, double alfa, double beta, int n, double prec, int kmax) {

	/*Definir funcions d'avaluacions*/
	/*Cal substituir per funcions correctes :
		- feval : funcio de la forma y''(x, y, y')
		- d2feval : dy''/dy
		- d3feval : dy''/dy'
	*/
	
	double feval(double x, double y, double z) {
		return (pow(x*z,2) - (9*pow(y,2)) + (4*pow(x,6))) / pow(x,5);
	}

	double d2feval(double x, double y, double z) {
		return (-18*y)/pow(x,5);
	}

	double d3feval(double x, double y, double z) {
		return (2*z)/pow(x,3);
	}

	/*Iteradors*/
	int i;

	/*Realitzem el pas de discretitzacio h i els nodes*/
	double h = (b-a)/(n+1);
	double* x = malloc((n+2) * sizeof(double));
	for(i = 0; i < n+2; i++) {
		x[i] = a + (i*h);
	}

	/*Trobar el vector y 0 aproximat*/
	double* y = malloc((n+2) * sizeof(double));
	for(i = 0; i < n+2; i++) {
		y[i] = alfa + ((beta-alfa)*(x[i]-a)/(b-a));
	}

	/*Guardar memoria per vectors*/
	double* e = malloc(n * sizeof(double));
	double* diaginf = malloc((n-1) * sizeof(double));
	double* diagmit = malloc(n * sizeof(double));
	double* diagsup = malloc((n-1) * sizeof(double));

	/*Repetir iteracions fins acabar*/
	int it = 0;
	while(1) {
		/*Calcular i preparar vectors*/
		for(i = 0; i < n-1; i++) {
			diagsup[i] = -1 + ((h/2) * d3feval(x[i+1], y[i+1], (y[i+2]-y[i])/(2*h)));
			diagmit[i] = 2 + (pow(h,2) * d2feval(x[i+1], y[i+1], (y[i+2]-y[i])/(2*h)));
			diaginf[i] = -1 - ((h/2) * d3feval(x[i+2], y[i+2], (y[i+3]-y[i+1])/(2*h)));
			e[i] = y[i] - (2*y[i+1]) + y[i+2] - (pow(h,2) * feval(x[i+1], y[i+1], (y[i+2]-y[i])/(2*h)));
		}
		diagmit[n-1] = 2 + (pow(h,2) * d2feval(x[n], y[n], (y[n+1]-y[n-1])/(2*h)));
		e[n-1] = y[n-1] - (2*y[n]) + y[n+1] - (pow(h,2) * feval(x[n], y[n], (y[n+1]-y[n-1])/(2*h)));

		/*Resoldre sistema per trobar e k*/
		d3(n, diaginf, diagmit, diagsup, e, prec);

		/*Comprovacions per acabar iteracions*/
		if(it == kmax) {
			goto stop;
		}
		double norma = infnorm(n, e);
		printf("Iteracio : %d // Norma : %25.16lf\n", it + 1, norma);
		if(norma < prec) {
			goto stop;
		}

		/*Si no sortim, preparem per seguent iteracio*/
		for(i = 0; i < n; i++) {
			y[i+1] = y[i+1] + e[i];
		}

		it = it + 1;
	}

	stop: printf("Hem acabat el proces\n");
	/*
	printf("Resultat final : punts (x,y) i error\n");
	double error;
	for(i = 0; i < n+2; i++) {
		error = fabs(y[i]-log(x[i])); 
		printf("%25.16lf %25.16lf %25.16lf\n", x[i], y[i], error);
	}
	*/
	printf("Resultat final : punts (x,y)\n");
	for(i = 0; i < n+2; i++) {
		printf("%25.16lf %25.16lf\n", x[i], y[i]);
	}
	/*
	printf("Resultat final : punts (x, error)\n");
	for(i = 0; i < n+2; i++) {
		error = fabs(y[i]-log(x[i])); 
		printf("%25.16lf %25.16lf\n", x[i], error);
	}
	printf("Resultat final : punts (x, arrel error)\n");
	for(i = 0; i < n+2; i++) {
		error = sqrt(fabs(y[i]-log(x[i]))); 
		printf("%25.16lf %25.16lf\n", x[i], error);
	}
	*/

	/*EXEMPLES*/
	/*Primer exercici
	double feval(double x, double y, double z) {
		return - pow(z,2) - y + log(x);
	}

	double d2feval(double x, double y, double z) {
		return -1;
	}

	double d3feval(double x, double y, double z) {
		return - 2*z;
	}

	double beta = log(2);
	ex1(1, 2, 0, beta, 100, 1e-10, 10);
	*/

	/*Segon exercici
	double feval(double x, double y, double z) {
		return pow(y,3) - (y*z);
	}

	double d2feval(double x, double y, double z) {
		return (3*pow(y,2)) - z;
	}

	double d3feval(double x, double y, double z) {
		return - y;
	}

	double alfa = 1.0/2.0;
	double beta = 1.0/3.0;
	ex1(1, 2, alfa, beta, 100, 1e-10, 10);
	*/

	/*Tercer exercici
	double feval(double x, double y, double z) {
		return z + (2*pow(y-log(x),3)) - pow(x,-1);
	}

	double d2feval(double x, double y, double z) {
		return (6*pow(y-log(x),2));
	}

	double d3feval(double x, double y, double z) {
		return 1;
	}

	double alfa = 1;
	double beta = (1.0/2.0) + log(2);
	ex1(1, 2, alfa, beta, 100, 1e-10, 10);
	*/

	/*Quart exercici
	double feval(double x, double y, double z) {
		return (pow(x*z,2) - (9*pow(y,2)) + (4*pow(x,6))) / pow(x,5);
	}

	double d2feval(double x, double y, double z) {
		return (-18*y)/pow(x,5);
	}

	double d3feval(double x, double y, double z) {
		return (2*z)/pow(x,3);
	}

	double alfa = 0;
	double beta = log(256);
	ex1(1, 2, alfa, beta, 100, 1e-10, 10);
	*/
}
