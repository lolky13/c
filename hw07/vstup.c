#include <stdio.h>
#include <stdlib.h>
#define MAX_INP 101



int append (int data[], size_t *size){
    int x = 0;
    char delimiter, colon;
    if (scanf("%c %c", &colon, &delimiter) != 2 || colon != ':' || delimiter != '{')
        return 0;
    /*if (colon != ':' || delimiter != '{')
        return 0;*/
    while ((scanf("%d %c", &x, &delimiter)) == 2){
        if (*size > 32)
            return 0;
        data[(*size)++] = x;
        if (delimiter == '\n')
            return 0;
        if (delimiter == '}')
            return 1;
    }
    if ( ! feof(stdin))
		return 0;
    return 1;
}

int input (int N[], int E[], int W[], int S[], size_t *Nsize, size_t *Esize, size_t *Wsize, size_t *Ssize, char side){
    if (side == 'N'){
        if ( ! append(N, Nsize))
            return 0;
    }
    else if (side == 'E'){
        if ( ! append(E, Esize))
            return 0;
    }
    else if (side == 'W'){
        if ( ! append(W, Wsize))
            return 0;
    }
    else if (side == 'S'){
        if ( ! append(S, Ssize))
            return 0;
    }
    else
        return 0;
    return 1;
}

int readInput(int N[], int E[], int W[], int S[], size_t *Nsize, size_t *Esize, size_t *Wsize, size_t *Ssize){
    char side1, side2, side3, side4;
    scanf("%c", &side1);
    printf(".%c.\n", side1);
    if ( ! input(N, E, W, S, Nsize, Esize, Wsize, Ssize, side1))
        return 0;
    scanf("%c", &side2);
    if (side2 == '\n')
        scanf("%c", &side2);
    if (side2 == side1)
        return 0;
    if ( ! input(N, E, W, S, Nsize, Esize, Wsize, Ssize, side2))
        return 0;
    scanf("%c", &side3);
    if (side3 == '\n')
        scanf("%c", &side3);
    if (side3 == side1 || side3 == side2)
        return 0;
    if ( ! input(N, E, W, S, Nsize, Esize, Wsize, Ssize, side3))
        return 0;
    scanf("%c", &side4);
    if (side4 == '\n')
        scanf("%c", &side4);
    if (side4 == side1 || side4 == side2 || side4 == side3)
        return 0;
    if ( ! input(N, E, W, S, Nsize, Esize, Wsize, Ssize, side4))
        return 0;
    return 1;
}


int main (void) {
    static int N[MAX_INP], E[MAX_INP], W[MAX_INP], S[MAX_INP];
    size_t Nsize = 0, Esize = 0, Wsize = 0, Ssize = 0;
    printf("Zetony:\n");
    if ( ! readInput (N, E, W, S, &Nsize, &Esize, &Wsize, &Ssize)){
        printf("Nespravny vstup.\n");
        return 0;
    }
    Nsize--;
    Esize--;
    Wsize--;
    Ssize--;
    printf("Asi v pohode.\n");
    return 0;
}