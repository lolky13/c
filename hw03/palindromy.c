#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int check (int rad, unsigned long long n){
    unsigned long long r = 0, n1 = n;
    /* Some algorithm that i found on the internet, i'm using it because is much faster than mine */
    while (n){
        r = r*rad + n % rad;
        n /= rad; 
    }
    return n1==r;
}

int nextPalindrome ( unsigned long long from, 
                     int radix,
                     unsigned long long * next )
{
if (radix<2 || radix>36)
    return 0;
if (from>= 18446744073709551615LLu)
    return 0;
from++;
while ((check(radix, from))!=1){
    from++;
}
*next = from;
return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  unsigned long long next;

  assert ( nextPalindrome ( 123, 10, &next ) == 1
           && next == 131 );
  assert ( nextPalindrome ( 188, 10, &next ) == 1
           && next == 191 );
  assert ( nextPalindrome ( 1441, 10, &next ) == 1
           && next == 1551 );
  assert ( nextPalindrome ( 95, 15, &next ) == 1
           && next == 96 ); /* 96 = 66 (radix 15) */
  assert ( nextPalindrome ( 45395, 36, &next ) == 1
           && next == 45431 ); /* 45431 = z1z (radix 36) */
  assert ( nextPalindrome ( 1027, 2, &next ) == 1
           && next == 1057 ); /* 1057 = 10000100001 (radix 2) */
  assert ( nextPalindrome ( 1000, 100, &next ) == 0
           && next == 1057 );
  assert ( nextPalindrome ( 18446744073709551614LLu, 2, &next ) == 1
           && next == 18446744073709551615LLu ); /* 18446744073709551615 = 1111111111111111111111111111111111111111111111111111111111111111 (radix 2) */
  assert ( nextPalindrome ( 18446744073709551615LLu, 2, &next ) == 0
           && next == 18446744073709551615LLu );
  return 0;
}
#endif /* __PROGTEST__ */