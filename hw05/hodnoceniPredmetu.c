#include <stdio.h>
#include <stdlib.h>

int intCmp (const int * a, const int * b){
  return (*b < *a) - (*a < *b);
}

int searchDown(int **data, int n, int x){
    int low = 0, res = -1, mid = 0;
    while (low <= n){
        mid = (low + n)/2;
        if (x == ((*data)[mid])){
            res = mid;
            n = mid - 1;
        }
        else if (x < ((*data)[mid])) {
            n = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return res;
}
int searchUp(int **data, int n, int x){
    int low = 0, res = -1, mid = 0;
    while (low <= n){
        mid = (low + n)/2;
        if (x == ((*data)[mid])){
            res = mid;
            low = mid + 1;
        }
        else if (x < ((*data)[mid])) {
            n = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return res;
}
int append (int **data, size_t *size, size_t *capacity){
    int x = 0;
    char delimiter;
    if (scanf("%c", &delimiter) != 1 || delimiter != '{')
        return 0;
    while ((scanf("%d %c", &x, &delimiter)) == 2){
        if (x<0 || x>1000000000)
            return 0;
        if (*size+2 > *capacity){
            *capacity = *capacity*2 + 50;
            *data = (int*)realloc(*data, sizeof(**data) * *capacity);
        }
        (*data)[(*size)++] = x;
        if (delimiter == '\n')
            return 0;
        if (delimiter == '}')
            return 1;        
    }
    if ( ! feof(stdin)){
		return 0;
    }
    return 1;
}

int main (void) {
    char s1, s2;
    size_t capacity = 0, size = 0;
    int lo = 0, hi = 0, down = 0, up = 0, num = 0;
    int *data = NULL;
    printf("Pocty bodu:\n");
    if ((append(&data, &size, &capacity)) == 0){
        free (data);
        printf("Nespravny vstup.\n");
        return 0;
    }
    qsort(data, size, sizeof(*data), (int(*)(const void *, const void *))intCmp);
    printf("Intervaly:\n");
    while ((scanf(" %c", &s1)) == 1){
        if ((scanf("%d;%d%c", &lo, &hi, &s2)) != 3){
            free (data);
            printf("Nespravny vstup.\n");
            return 0;
        }
        if ((s1 == '<') && (s2 == '>')){
            num = 0;
            for (int i = lo; i <= hi; i++){
                up = searchUp(&data, size-1, i);
                if ((down = searchDown(&data, size-1, i)) != -1){
                    num += up - down + 1;
                }
            }
        }
        else if ((s1 == '<') && (s2 == ')')){
            num = 0;
            for (int i = lo; i < hi; i++){
                down = searchDown(&data, size-1, i);
                up = searchUp(&data, size-1, i);
                if (down != -1){
                    num += up - down + 1;
                }
            }
        }
        else if ((s1 == '(') && (s2 == '>')){
            num = 0;
            for (int i = lo + 1; i <= hi; i++){
                down = searchDown(&data, size-1, i);
                up = searchUp(&data, size-1, i);
                if (down != -1){
                    num += up - down + 1;
                }
            }
        }
        else if ((s1 == '(') && (s2 == ')')){
            num = 0;
            for (int i = lo + 1; i < hi; i++){
                down = searchDown(&data, size-1, i);
                up = searchUp(&data, size-1, i);
                if (down != -1){
                    num += up - down + 1;
                }
            }
        }
        else{
            free (data);
            printf("Nespravny vstup.\n");
		    return 0;
        }
        printf(" -> %d\n", num);
    }
    if ( ! feof(stdin)){
		free (data);
        printf("Nespravny vstup.\n");
		return 0;
    }
    free (data);
    return 0;
}