#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int isLeap(int year){	/* algorithm to terminate leap years */
	if (year%4000==0){
		return false;
	}
	if (year%400==0){
		return true;
	}
	if (year%100==0){
		return false;
	}
	if (year%4==0){
		return true;
	}
	return false;
}

int monthsToDays(int month, int year){			/* prevod mesicu na dny */
	unsigned long long day=0;
        if (isLeap(year)){
                int days[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
		for (int i=1; i< month; i++){
                        day += days[i - 1];
                }
                return day;
        }
        int days1[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
        for (int i=1; i< month; i++){
                day += days1[i-1];
	}
	return day;
}

int yearsToDays(int y){			/* prevod roku na dny */
	int leapYears = y/4 - y/100 + y/400 - y/4000 - 387;
	int notLeaps = y - 1600 - leapYears;
	return ((leapYears * 366) + (notLeaps * 365));
}

int hoursRings (int h){
        int b=0;
        switch (h){
                case 0:
                        b +=12;
                case 1:
                        b +=1;
		case 2:
                        b +=2;
                case 3:
                        b +=3;
                case 4:
                        b +=4;
                case 5:
                        b +=5;
                case 6:
                        b +=6;
                case 7:
                        b +=7;
                case 8:
                        b +=8;
                case 9:
                        b +=9;
                case 10:
                        b +=10;
                case 11:
                        b +=11;
                case 12:
                        b +=12;
                case 13:
			b += 1;
		case 14:
                        b += 2;
		case 15:
                        b += 3;
                case 16:
                        b += 4;
		case 17:
                        b += 5;
                case 18:
                        b += 6;
		case 19:
                        b += 7;
                case 20:
                        b += 8;
                case 21:
                        b += 9;
                case 22:
                        b += 10;
		case 23:
                        b += 11;
        }
        return b;
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 ){

	unsigned long long int1=0, int2=0, days1=0, days2=0;
        long long be1=0, be2=0;

	if ( y1 < 1600 || y2 < 1600 || m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12 || d1 < 1 || d2 < 1||h1 < 0 || h1 > 23 || h2 < 0 || h2 > 23 || m1 < 0 || m1 > 59 || m2 < 0 || m2 > 59){
		return 0;
	}
	
	if (m1 == 1 || m1 == 3 || m1 == 5 || m1 == 7 || m1 == 8 || m1 == 10 || m1 == 12 || m2 == 1 || m2 == 3 || m2 == 5 || m2 == 7 || m2 == 8 || m2 == 10 || m2 == 12){
		if (d1 > 31 || d2 > 31){
                        return 0;	/* wrong days for months with 31 days */
	        }
        } 
	if (m1 == 4 || m1 == 6 || m1 == 9 || m1 == 11 || m2 == 4 || m2 == 6 || m2 == 9 || m2 == 11){
		if (d1 > 30 || d2 > 30){
                        return 0;	/* wrong days for months with 30 days */
	        }
        }
        if (isLeap(y1)){
	        if (m1 == 2){
	        	if (d1 > 29)
                                return 0;	/* wrong days for february 1 in leap */
	        }
        }
        else if (m1 == 2){
                if ( d1 > 28)
                        return 0;
        }
	if (isLeap(y2)){
	        if (m2 == 2){
	        	if (d2 > 29)
                                return 0;
	        }
        }
        else if (m2 == 2){
                if ( d2 > 28)
                        return 0;
        }
	/* Converting intervals into days and minutes */
	days1= d1 + monthsToDays(m1,y1) + yearsToDays(y1);
	days2= d2 + monthsToDays(m2,y2) + yearsToDays(y2) - 1;
	int1 = i1 + h1*60 + (days1-1)*1440;
	int2 = i2 + h2*60 + days2*1440;

	if (int1>int2){
		return 0;
	}
        if (int1==int2){
                return 1;
        }
        if (d1==d2 && m1==m2 && y1==y2 && ((days1-1)%7) == 0){
                return 1;
        }
	if (d1==d2 && m1==m2 && y1==y2 && ((days1-1)%7) != 0){		/* Odbiti zvonu pokud je interval ve stejny den */
                int min1 = i1 + h1*60;
                int min2 = i2 + h2*60;
                while ((min1%60)% 15 != 0){
                        min1++;
                }
		while ((min2%60) % 15 != 0){
                        min2--;
                }
		if (min1>min2){
			*b1 = 0;
			*b2 = 0;
			return 1;
		}
		while (min1<min2){		/* stupid program velice hodne */
			int a = min1%60;
                        if (a==0){
				be1 += 4;
                                be2 += hoursRings(min1/60);

			}
			else{
                         	be1 += a / 15;
			}
                        min1 += 15;
		}
                *b1 = be1;
                *b2 = be2;
                printf("%lld %lld", be1, be2);
		return 1;
	}
	
	if (((days1 - 1)%7) != 0){		/* Odbiti zvonu v den zacinajiciho intervalu */
		while (i1 % 15 == 0){
			i1++;
		}
		while (h1 != 24){
			if (i1==0){
				be1 += 4;
			}
			if (h1==0){
				be2 += 12;
			}
			while (i1 != 60){
				be1 += i1 / 15;
				i1 += 15;
			}
			i1 = 0;
			h1++;
                        be2 += hoursRings(h1);
		}
	}	

	if (((days1-1)%7) != 0){		/* Odbiti zvonu v den konciciho intervalu */
		while (i2 % 15 != 0){
			i2--;
		}
		while (h2 > -1){
                        while (i2 > -1){
                                be1 += i2 / 15;
				if (i2==0){
					be1 += 4;
				}
                                i2 -= 15;
                        }
                        i2 = 45;
                        be2 += hoursRings(h2);
			h2--;
                }
	}
	if (days1==days2){
                *b1 = be1;
                *b2 = be2;
		return 1;
	}
	unsigned long long daysDiff=0, days1Temp=0;
	days1Temp=days1;		
	daysDiff= days2-days1;		/* 2.1.1600 je nedele */
	while (days1Temp>days2){	/* odbiti zvonu mezi intervaly */
		if ((days1Temp % 7) ==0){
			unsigned long long y=0;
			y = daysDiff -((daysDiff - (days1Temp - days1))/7);
			be1 += y * 240;
			be2 += y * 156;
                        *b1 = be1;
                        *b2 = be2;
			return 1;
		}
		days1Temp++;
	}
	be1 += daysDiff * 240;
	be2 += daysDiff * 156;
        *b1 = be1;
        *b2 = be2;
	return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2;

  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );
  assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  2, 11, 20, &b1, &b2 ) == 1
           && b1 == 106
           && b2 == 65 );
  assert ( bells ( 2022, 10,  2, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 115
           && b2 == 78 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022,  1,  1, 13, 15,
                   2022, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 56861
           && b2 == 36959 );
  assert ( bells ( 2019,  1,  1, 13, 15,
                   2019, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2024,  1,  1, 13, 15,
                   2024, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57341
           && b2 == 37271 );
  assert ( bells ( 1900,  1,  1, 13, 15,
                   1900, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2022, 10,  1,  0,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 124
           && b2 == 90 );
  assert ( bells ( 2022, 10,  1,  0, 15,
                   2022, 10,  1,  0, 25, &b1, &b2 ) == 1
           && b1 == 1
           && b2 == 0 );
  assert ( bells ( 2022, 10,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 11,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 10, 32, 12,  0,
                   2022, 11, 10, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2100,  2, 29, 12,  0,
                   2100,  2, 29, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2000,  2, 29, 12,  0,
                   2000,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2004,  2, 29, 12,  0,
                   2004,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 0
           && b2 == 0 );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */