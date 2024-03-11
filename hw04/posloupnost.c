#include <stdio.h>
#include <stdlib.h>
#define MAX_INP 2000
#define MAX_SUM 99999999

int calcSuma ( int *data, int *suma, int z){	/*calculating suma of all intervals*/
	int c=0, y=0, m=0;								/*its working*/
	for ( int i = 0; i != z; i++ ){
		for (int j = i+1; j != z; j++){
			for (int k = i; k != j+1; k++){
				c += data[k];
			}
			suma[y++] = c;
			m++;
			c = 0;
		}
	}
	return m;
}

int intCmp (const int * a, const int * b){
  return (*b < *a) - (*a < *b);
}


int celkem (int *suma, int n){	/*pocitani dvojic*/
	int x=0, i=0, l=0;
	qsort(suma, n, sizeof(*suma), (int(*)(const void *, const void *))intCmp);
	while (i != n){
		l = i+1;
		while (suma[i]==suma[l]){
			x++;
			l++;
		}
		i++;
	}
	return x;
}

int main (void){
	
	int data[MAX_INP];
	static int suma[MAX_SUM];
	int n=0, size=0, m=0;

	printf("Posloupnost:\n");
	while ((scanf("%d", data + size++)) == 1){
		n++;
		if (size > 1999){
			printf("Nespravny vstup.\n");
			return 0;
		}
	}
	if ( ! feof(stdin)){
		printf("Nespravny vstup.\n");
		return 0;
	}
	if (n==0){
		printf("Nespravny vstup.\n");
		return 0;
	}
	m = calcSuma(data, suma, n);
	printf("Pocet dvojic: %d\n", celkem(suma, m));
	return 0;
}
