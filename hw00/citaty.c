#include <stdio.h>
#include <string.h>


int main (void){
	int a=0;
	char  arr[9][150] = {"Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n",
	       "Qapla'\nbortaS bIr jablu'DI' reH QaQqu' nay'.\n",
	      "Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n",
	     "Qapla'\nbISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n",
	     "Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n",
	    "Qapla'\nSuvlu'taHvIS yapbe' HoS neH.\n",
	   "Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n",
	  "Qapla'\nHeghlu'meH QaQ jajvam.\n",
	 "Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n"};
	printf("ml' nob:\n");
	if (scanf("%d",&a)!=1){
		printf("luj\n");
		return 0;
	}
	else if (feof(stdin)){	
		printf("luj\n");
                return 0;
	}
	else if ((a>0) & (a<10)){
		printf("%s", arr[a-1]);
		return 0;
	}
	else {	
		printf("luj\n");
                return 0;
	}	
	return 0;
}
