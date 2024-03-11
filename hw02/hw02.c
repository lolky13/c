#include <stdio.h>
#include <iostream>
#include <math.h>

int prime(int n){		/*O(sqrt(N)) method to check if a number is prime or not */
	if ((n==1) || (n==0)){
		return false;
	}
	int l = 2;
	while (l*l <= n) {
		if (n % l == 0){
			return false;
		}
		l++;
	}
	return true;
}

int is_div(int m){		/*all divisors are present in pairs -> so we can speed up the program */
	int divs = 0;
	for (int o=1; o<= sqrt(m); o++){
		if (m%o == 0){
			if (m/o == o){
				divs +=o;
			}
			else {
				divs +=o;
				divs +=(m/o);
			}
		}
	}
	divs -= m;
	return divs;
}

int main (void){
	char operace;
	int lo=0, hi=0, divisors=0, amount=0;

	printf ("Intervaly:\n");
	while ((scanf("%s", &operace)) == 1){
		if ((scanf("%d", &lo)) != 1){
			printf("Nespravny vstup.\n");
			return 0;
		}
		if ((scanf("%d", &hi)) != 1){
			printf("Nespravny vstup.\n");
			return 0;
		}
		if ((lo < 1) || (hi < lo)){
			printf("Nespravny vstup.\n");
			return 0;
		}
		else if ((operace == '?') || (operace == '#')){
	
			amount = 0;
			for (int j = lo; j <= hi; j++){
				divisors = is_div(j);
				if (prime(divisors)){
					amount += 1;
					if ( operace == '?'){
						printf ("%d\n", j);
					}
				}		
			}
			printf("Celkem: %d\n", amount);
		}
		else {
			printf("Nespravny vstup.\n");
			return 0;
		}
	}
	
	if ( ! feof(stdin)){
		printf("Nespravny vstup.\n");
		return 0;
	}
	
	return 0;
}
