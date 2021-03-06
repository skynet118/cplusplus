#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


void generate_vector(int *v, int size) {
    for(int i = 0; i < size; i++) {
        v[i] = rand() % 10;
    }
}

void print_vector(int *v, int size) {
    for(int i = 0; i < size; i++) {
        printf("%2d ", v[i]);
    }
    printf("\n");
}

void multiply_vectors(int *v1, int *v2, int *result, long start, long stop) {
    for(int i=start; i<stop; i++) {
        result[i - start] = v1[i] * v2[i];
    }
}

int main() {
    int SIZE = 100000000;
    int *vector1;
    int *vector2;
    int *result;

    vector1 = malloc(sizeof(int) * SIZE);
    vector2 = malloc(sizeof(int) * SIZE);
    result = malloc(sizeof(int) * SIZE);

    generate_vector(vector1, SIZE);
    generate_vector(vector2, SIZE);

    multiply_vectors(vector1, vector2, result, 0, SIZE);

    if (SIZE < 20) {
        print_vector(vector1, SIZE);
        print_vector(vector2, SIZE);
        print_vector(result, SIZE);
    }

    free(vector1);
    free(vector2);
    free(result);
}