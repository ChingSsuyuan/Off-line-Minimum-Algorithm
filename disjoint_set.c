#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_n 150
#define max_m 50

typedef struct 
{
    int *elements;
    int size;
    int capacity;
}disjoint_set;

disjoint_set *sets[max_m+1];
int extracted[max_n];
int Index=0;
disjoint_set* create(int capacity){
    disjoint_set *set=(disjoint_set*)malloc(sizeof(disjoint_set));
    set->elements=(int*)malloc(sizeof(int)*capacity);
    set->size=0;
    set->capacity = capacity;
    return set;
}

void insert(disjoint_set *set, int key){
    if (set->size<set->capacity)
    {
        set->elements[set->size++]=key;
    }
}

void unionSets(disjoint_set* set1, disjoint_set* set2) {
    for (int i = 0; i < set2->size; i++) {
        insert(set1, set2->elements[i]);
    }
    free(set2->elements);
    free(set2);
}

void offLineMinimum_in_order(int m, int n, int op[]) {
    for (int i = 0; i <= m; i++) {
        sets[i] = create(n);
    }
    int setIndex = 0;
    for (int i = 0; i < m; i++) {
        if (op[i] == -1) { 
            setIndex++;
        } else { 
            insert(sets[setIndex], op[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        int j;
        for (j = 0; j <= m; j++) {
            int* found = NULL;
            for (int k = 0; k < sets[j]->size; k++) {
                if (sets[j]->elements[k] == i) {
                    found = &sets[j]->elements[k];
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        if (j != m + 1) {
            extracted[Index++] = i;
            int l = j + 1;
            while (l <= m && sets[l]->size == 0) {
                l++;
            }
            if (l <= m) {
                unionSets(sets[l], sets[j]);
                sets[j] = create(n);
            }
        }
    }

    printf("Extratced in order:\n");
    // for (int i = 1; i <= Index; i++) {
    //     printf("index %d is %d ", i,extracted[i]);
    // }
    for (int i = 0; i < Index; i++) {
        printf("%4d ", extracted[i]);
        if ((i + 1) % 10 == 0) {
        printf("\n");
        }
    }
}
void offLineMinimum(int m, int n, int op[]) {
    int setCount = 0;
    int currentSet = 0;
    int extractedCount = 0;
    for (int i = 0; i <= n; i++) {
        sets[i] = create(m);
    }
    for (int i = 0; i < n; i++) {
        if (op[i] == -1) { // 'E' operation
            int minElement = -1;
            int minSetIndex = -1;
            for (int j = 0; j <= currentSet; j++) {
                for (int k = 0; k < sets[j]->size; k++) {
                    if (minElement == -1 || sets[j]->elements[k] < minElement) {
                        minElement = sets[j]->elements[k];
                        minSetIndex = j;
                    }
                }
            }
            if (minElement != -1) {
                extracted[extractedCount++] = minElement;
                for (int j = 0; j < sets[minSetIndex]->size; j++) {
                    if (sets[minSetIndex]->elements[j] == minElement) {
                        for (int k = j; k < sets[minSetIndex]->size - 1; k++) {
                            sets[minSetIndex]->elements[k] = sets[minSetIndex]->elements[k + 1];
                        }
                        sets[minSetIndex]->size--;
                        break;
                    }
                }
            }
            currentSet++;
        } else {
            insert(sets[currentSet], op[i]);
        }
    }
    printf("Extracted:\n");
    for (int i = 0; i < extractedCount; i++) {
        printf("%4d ", extracted[i]);
        if ((i + 1) % 10 == 0) {
        printf("\n");
        }
    }
}
int main() {
    FILE *file = fopen("test.txt", "r");
    int m = 0;
    int op[max_n];
    char buffer[150];
    while (fscanf(file, "%s", buffer) != EOF && m < max_n) {
        if (strcmp(buffer, "E") == 0) {
            op[m++] = -1; 
        } else {
            op[m++] = atoi(buffer);
        }
    }
    fclose(file);
    printf("---------------------------------------------------\n");
    printf("Inserted:");
    for (int i = 0; i < m; i++) {
        if (op[i] == -1) {
            printf("E ");
        } else {
            printf("%d ", op[i]);
        }
    }
    printf("\n");
    printf("---------------------------------------------------\n");
    int max_size = 0;

    // Count the maximum number of elements in any set
    int n=m;
    int size = 0;
    for (int i = 0; i < n; i++) {
        if (op[i] == -1) {
            if (size > max_size) {
                max_size = size;
            }
            size = 0;
        } else {
            size++;
        }
    }
    if (size > max_size) {
        max_size = size;
    }
    offLineMinimum(max_size, n ,op);
    for (int i = 0; i <= m; i++) {
        free(sets[i]->elements);
        free(sets[i]);
    }
    printf("\n");
    printf("---------------------------------------------------\n");
    offLineMinimum_in_order(max_n, max_m ,op);
    for (int i = 0; i <= m; i++) {
        free(sets[i]->elements);
        free(sets[i]);
    }
    printf("\n");
    printf("---------------------------------------------------\n");
    return 0;
}
