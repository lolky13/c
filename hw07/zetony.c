#include <stdio.h>
#include <stdlib.h>
#define MAX_INP 32
#define MIN_INT -2147483647
#define TOKEN_MAX 128

//struct for storing gameplays
typedef struct {
    int A;
    int B;
    char side[TOKEN_MAX];
    size_t index[TOKEN_MAX];
    int points[TOKEN_MAX];
} score;

//appending lists of tokens
//returning 1 if okay, 0 if not
int append (int data[], size_t *size){
    int x = 0;
    char delimiter, colon;
    if (scanf("%c %c", &colon, &delimiter) != 2 || colon != ':' || delimiter != '{')
        return 0;
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

//determining where the tokens are and calling function append
//returning 1 if okay, 0 if not
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

//checking the recurrent sides
//returning 1 if the input is okay, 0 if not
int readInput(int N[], int E[], int W[], int S[], size_t *Nsize, size_t *Esize, size_t *Wsize, size_t *Ssize){
    char side1, side2, side3, side4;
    scanf("%c", &side1);
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

//main algorithm for best outcome of the game
score gameRecursive(int *N, int *E, int *W, int *S, size_t Nsize, size_t Esize, size_t Wsize, size_t Ssize, size_t Nindex, size_t Eindex, size_t Windex, size_t Sindex, size_t player, size_t tokens, int sumA, int sumB, size_t bodyIndex){
    score sum, tmp;
    //condition for the end of the game(there are no tokens to take left)
    if ((Nsize + Esize + Wsize + Ssize + 4)==(tokens)){
        tmp.A = sumA;
        tmp.B = sumB;
        return tmp;
    }
    sum.A = MIN_INT;
    sum.B = MIN_INT;
    //trying all possible token takes for player A
    if (player){
        if (Nindex <= Nsize){
            tmp = gameRecursive(N, E, W, S, Nsize, Esize, Wsize, Ssize, Nindex + 1, Eindex, Windex, Sindex, 0, tokens + 1, sumA + N[Nindex], sumB, bodyIndex + 1);
            //if the returned score is better, rewrite it and add the step
            if (tmp.A > sum.A){
                sum = tmp;
                sum.side[bodyIndex] = 'N';
                sum.index[bodyIndex] = Nindex;
                sum.points[bodyIndex] = N[Nindex];
            }
        }
        if (Eindex <= Esize){
            tmp = gameRecursive(N, E, W, S, Nsize, Esize, Wsize, Ssize, Nindex, Eindex + 1, Windex, Sindex, 0, tokens + 1, sumA + E[Eindex], sumB, bodyIndex + 1);
            //if the returned score is better, rewrite it and add the step
            if (tmp.A > sum.A){
                sum = tmp; 
                sum.side[bodyIndex] = 'E';
                sum.index[bodyIndex] = Eindex;
                sum.points[bodyIndex] = E[Eindex];
            }
        }
        if (Windex <= Wsize){
            tmp = gameRecursive(N, E, W, S, Nsize, Esize, Wsize, Ssize, Nindex, Eindex, Windex + 1, Sindex, 0, tokens + 1, sumA + W[Windex], sumB, bodyIndex + 1);
            //if the returned score is better, rewrite it and add the step
            if (tmp.A > sum.A){
                sum = tmp;
                sum.side[bodyIndex] = 'W';
                sum.index[bodyIndex] = Windex;
                sum.points[bodyIndex] = W[Windex];
            }
        }
        if (Sindex <= Ssize){
            tmp = gameRecursive(N, E, W, S, Nsize, Esize, Wsize, Ssize, Nindex, Eindex, Windex, Sindex + 1, 0, tokens + 1, sumA + S[Sindex], sumB, bodyIndex + 1);
            //if the returned score is better, rewrite it and add the step
            if (tmp.A > sum.A){
                sum = tmp;
                sum.side[bodyIndex] = 'S';
                sum.index[bodyIndex] = Sindex;
                sum.points[bodyIndex] = S[Sindex];
            }
        }
    }
    //trying all possible token takes for player B
    else{
        if (Nindex <= Nsize){
            tmp = gameRecursive(N, E, W, S, Nsize, Esize, Wsize, Ssize, Nindex + 1, Eindex, Windex, Sindex, 1, tokens + 1, sumA, sumB + N[Nindex], bodyIndex + 1);
            //if the returned score is better, rewrite it and add the step
            if (tmp.B > sum.B){
                sum = tmp;
                sum.side[bodyIndex] = 'N';
                sum.index[bodyIndex] = Nindex;
                sum.points[bodyIndex] = N[Nindex];
            }
        }
        if (Eindex <= Esize){
            tmp = gameRecursive(N, E, W, S, Nsize, Esize, Wsize, Ssize, Nindex, Eindex + 1, Windex, Sindex, 1, tokens + 1, sumA, sumB + E[Eindex], bodyIndex + 1);
            //if the returned score is better, rewrite it and add the step
            if (tmp.B > sum.B){
                sum = tmp;
                sum.side[bodyIndex] = 'E';
                sum.index[bodyIndex] = Eindex;
                sum.points[bodyIndex] = E[Eindex];
            }
        }
        if (Windex <= Wsize){
            tmp = gameRecursive(N, E, W, S, Nsize, Esize, Wsize, Ssize, Nindex, Eindex, Windex + 1, Sindex, 1, tokens + 1, sumA, sumB + W[Windex], bodyIndex + 1);
            //if the returned score is better, rewrite it and add the step
            if (tmp.B > sum.B){
                sum = tmp;
                sum.side[bodyIndex] = 'W';
                sum.index[bodyIndex] = Windex;
                sum.points[bodyIndex] = W[Windex];
            }
        }
        if (Sindex <= Ssize){
            tmp = gameRecursive(N, E, W, S, Nsize, Esize, Wsize, Ssize, Nindex, Eindex, Windex, Sindex + 1, 1, tokens + 1, sumA, sumB + S[Sindex], bodyIndex + 1);
            //if the returned score is better, rewrite it and add the step
            if (tmp.B > sum.B){
                sum = tmp;
                sum.side[bodyIndex] = 'S';
                sum.index[bodyIndex] = Sindex;
                sum.points[bodyIndex] = S[Sindex];
            }
        }
    }
    //returning best gameplay
    return sum;
}

//help function to call gameRecursive and to print the best gameplay
void game(int *N, int *E, int *W, int *S, size_t Nsize, size_t Esize, size_t Wsize, size_t Ssize){
    score outcome;
    size_t pulls = 0;
    int player = 0;
    pulls = Nsize + Esize + Wsize + Ssize;
    outcome = gameRecursive(N, E, W, S, Nsize - 1, Esize - 1, Wsize - 1, Ssize - 1, 0, 0, 0, 0, 1, 0, 0, 0, 0);
    for (size_t i = 0; i < pulls; i++){
        printf("%c: %c[%ld] (%d)\n", 'A' + player, outcome.side[i], outcome.index[i], outcome.points[i]);
        player = ! player;
    }
    printf("Celkem A/B: %d/%d\n", outcome.A, outcome.B);
}

int main (void) {
    static int N[MAX_INP], E[MAX_INP], W[MAX_INP], S[MAX_INP];
    size_t Nsize = 0, Esize = 0, Wsize = 0, Ssize = 0;
    printf("Zetony:\n");
    if ( ! readInput (N, E, W, S, &Nsize, &Esize, &Wsize, &Ssize)){
        printf("Nespravny vstup.\n");
        return 0;
    }
    game(N, E, W, S, Nsize, Esize, Wsize, Ssize);
    return 0;
}