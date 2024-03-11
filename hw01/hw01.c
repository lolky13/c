#include <stdio.h>
#include <math.h>


int main (void){
	double kreU=0, debU=0, withdrawal=0, balanceTemp1=0;
	int balance=0, dayInput=0, dayChange=0,  deposit=1;
	
	printf("Zadejte kreditni urok [%%]:\n");
	if ((scanf("%lf", &kreU))!=1){
		printf("Nespravny vstup.\n");
		return 0;
	}
	else if ((kreU<=0) & (kreU>100)){
		printf("Nespravny vstup.\n");
		return 0;
	}

	printf("Zadejte debetni urok [%%]:\n");

	if ((scanf("%lf", &debU))!=1){
		printf("Nespravny vstup.\n");
		return 0;
	}
	else if ((debU<=0) || (debU>100)){
		printf("Nespravny vstup.\n");
		return 0;
	}
	printf("Zadejte transakce:\n");

	if ((scanf(" %d , %d", &dayInput, &deposit)) != 2){
		printf("Nespravny vstup.\n");
		return 0;
	}
	else if (deposit == 0){
		printf("Zustatek: 0.00");
		return 0;
	}
	int dayPeriod=0, balanceTemp=0;
	dayPeriod = (dayInput - dayChange);
	dayChange = dayInput;
	if (balance < 0){
		for (int i=0; i<dayPeriod; i++){
			balanceTemp1 = balance/100.0;
			balanceTemp = ((balanceTemp1*(1+(debU/100)) - balanceTemp1)*100);
			/*balanceTemp = ((floor(balanceTemp*100))/100); */
			balance += balanceTemp;
		}
	}
	else {
		for (int i=0; i<dayPeriod; i++){
			balanceTemp1 = balance/100.0;
			balanceTemp = ((balanceTemp1*(1+(kreU/100)) - balanceTemp1)*100);
			/*balanceTemp = ((floor(balanceTemp*100))/100);*/
			balance += balanceTemp;
		}
	}
	balance += deposit*100;
	
	while (deposit !=0){
		if ((scanf(" %d , %d", &dayInput, &deposit)) != 2){
			printf("Nespravny vstup.\n");
			return 0;
		}
		else if (dayInput <= dayChange){
			printf("Nespravny vstup.\n");
			return 0;
		}
		dayPeriod = (dayInput - dayChange);
		dayChange = dayInput;
		if (balance < 0){
			for (int i=0; i<dayPeriod; i++){
				balanceTemp1 = balance/100.0;
				balanceTemp = ((balanceTemp1*(1+(debU/100)) - balanceTemp1)*100);
				/*balanceTemp = ((floor(balanceTemp*100))/100);*/
				balance += balanceTemp;
			}
		}
		else {
			for (int i=0; i<dayPeriod; i++){
				balanceTemp1 = balance/100.0;
				balanceTemp = ((balanceTemp1*(1+(kreU/100)) - balanceTemp1)*100);
				/*balanceTemp = ((floor(balanceTemp*100))/100);*/
				balance += balanceTemp;
			}
		}
		balance += deposit*100;
	}
	withdrawal = balance/100.0;
	printf("Zustatek: %.2lf\n", withdrawal);
	return 0;
}