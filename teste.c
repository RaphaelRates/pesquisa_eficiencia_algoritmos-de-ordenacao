#include <stdio.h>
#include <stdbool.h>

typedef void (*func1)(int*, int, unsigned long*, unsigned long*);
typedef void (*func2)(float*, double, unsigned long*);

void exemploFunc1(int *a, int b, unsigned long *c, unsigned long *d) {
    // Função de exemplo que corresponde ao tipo func1
}

void exemploFunc2(float *a, double b, unsigned long *c) {
    // Função de exemplo que corresponde ao tipo func2
}

bool is_func1_or_func2_type(void *func) {
    // Faz o cast para func1 e verifica se não é NULL
    func1 casted_func1 = (func1)func;
    if (casted_func1 != NULL) {
        return true;
    }

    // Faz o cast para func2 e verifica se não é NULL
    func2 casted_func2 = (func2)func;
    if (casted_func2 != NULL) {
        return true;
    }

    return false;
}

int main() {
    void *func_ptr1 = (void *)exemploFunc1;
    void *func_ptr2 = (void *)exemploFunc2;

    if (is_func1_or_func2_type(func_ptr1)) {
        printf("func_ptr1 é do tipo func1 ou func2.\n");
    } else {
        printf("func_ptr1 NÃO é do tipo func1 ou func2.\n");
    }

    if (is_func1_or_func2_type(func_ptr2)) {
        printf("func_ptr2 é do tipo func1 ou func2.\n");
    } else {
        printf("func_ptr2 NÃO é do tipo func1 ou func2.\n");
    }

    return 0;
}