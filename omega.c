#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <limits.h>
#include "style.h"

typedef struct {
    void (*func)(int *, int, unsigned long *, unsigned long *);
    int n;
    unsigned long int duracao;
    unsigned long int comparacoes;
    unsigned long int trocas;
    BOOL recursive;
} ArgsBubble;

//================================== VETORES ===================================
void alocar_vetor(int **vetor, int n) {
    if (n > 0) {
        *vetor = (int *)malloc(n * sizeof(int));
        if (*vetor == NULL) {
            fprintf(stderr,RED"ERROR:"CYAN" Falha na alocação de memória."RESET"\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, RED"ERROR:"CYAN" Número de alocação inválido."RESET"\n");
        exit(EXIT_FAILURE);
    }
}

void preencher_vetor(int *vetor, int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        vetor[i] = min + rand() % (max - min + 1);
    }
}

void imprimir_vetor(const int *vetor, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

//================================ ALGORITMOS ==================================
void bubble_sort(int *vetor, int n, unsigned long *comparacoes, unsigned long *trocas) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas)++;
            }
        }
    }
}

DWORD WINAPI testar_algoritmo(LPVOID args) {
    ArgsBubble* argumentos = (ArgsBubble*)args;
    int *vetor = NULL;
    clock_t inicio, fim;

    alocar_vetor(&vetor, argumentos->n);
    preencher_vetor(vetor, argumentos->n, 0, argumentos->n * 10);

    argumentos->comparacoes = 0;
    argumentos->trocas = 0;

    inicio = clock();
    argumentos->func(vetor, argumentos->n, &argumentos->comparacoes, &argumentos->trocas);
    fim = clock();

    argumentos->duracao = (fim - inicio) * 1000 / CLOCKS_PER_SEC;
    printf(NEGRITO YELLOW"EXECUTADO"RESET" em "GREEN"%lu"RESET" ms, com "GREEN"%lu "RESET"comparacoes e "GREEN"%lu "RESET"trocas.\n", 
           argumentos->duracao, argumentos->comparacoes, argumentos->trocas);

    free(vetor);
    return 0;
}

void executar_teste(int tamanho) {
    ArgsBubble args;
    args.func = bubble_sort;
    args.n = tamanho;

    unsigned long int total_duracao = 0, min_duracao = ULONG_MAX, max_duracao = 0;
    unsigned long int total_comparacoes = 0, total_trocas = 0;

    for (int i = 0; i < 10; i++) {
        HANDLE thread = CreateThread(NULL, 0, testar_algoritmo, &args, 0, NULL);
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);

        total_duracao += args.duracao;
        total_comparacoes += args.comparacoes;
        total_trocas += args.trocas;

        if (args.duracao < min_duracao) min_duracao = args.duracao;
        if (args.duracao > max_duracao) max_duracao = args.duracao;
    }
    printf(CYAN"-------------------------------------------------------------------------------------------------------------"RESET);
    printf("\n"CYAN ITALIC"TAMANHO DO VETOR"RESET"  |  "CYAN ITALIC"MEDIA DO TEMPO"RESET"  |  "CYAN ITALIC"DIFERENCA DE TEMPO"RESET"  | "CYAN ITALIC" MEDIA DE COMPARACAO "RESET" |  "CYAN ITALIC"MEDIA DE TROCAS"RESET"  |\n");
    printf("     "GREEN NEGRITO"%d"RESET"          |       "GREEN NEGRITO"%lu"RESET"         |          "GREEN NEGRITO"%lu"RESET"         |        "GREEN NEGRITO"%lu"RESET"       |      "GREEN NEGRITO"%lu"RESET"      |\n", tamanho,total_duracao / 10, max_duracao - min_duracao, total_comparacoes / 10, total_trocas / 10);
    printf(CYAN"-------------------------------------------------------------------------------------------------------------"RESET"\n\n");
}

int main() {


    executar_teste(10);
    executar_teste(100);
    executar_teste(1000);
    executar_teste(10000);

    return 0;
}
