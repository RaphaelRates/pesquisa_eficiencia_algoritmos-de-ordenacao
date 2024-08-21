#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "biblioteca.h"
#include <limits.h>
#include "ordination.h"
#include "style.h"

//================================== VERRIFICAR FUNÇÃO ==========================
#include <stdio.h>
#include <stdbool.h>

typedef void (* iteractive)(int*, int,  unsigned long*, unsigned long*);
typedef void (* recursive)(int*, int, int, unsigned long*, unsigned long*);

void exemploFunc1(int *a, int b, unsigned long *c, unsigned long *d) {
    // Função de exemplo que corresponde ao tipo func1
}

void exemploFunc2(float *a, double b, unsigned long *c) {
    // Função de exemplo que corresponde ao tipo func2
}

bool is_func1_or_func2_type(void *func) {
    iteractive casted_func1 = (iteractive)func;
    if (casted_func1 != NULL) {
        return true;
    }
    recursive casted_func2 = (recursive)func;
    if (casted_func2 != NULL) {
        return true;
    }

    return false;
}

//================================== VETORES ===================================
void alocar_vetor(int **vetor, int n) {
    if (n > 0) {
        *vetor = (int *)malloc(n * sizeof(int));
        if (*vetor == NULL) {
            fprintf(stderr, RED "ERROR:" CYAN " Falha na alocação de memoria." RESET "\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, RED "ERROR:" CYAN " Numero de alocação invalido." RESET "\n");
        exit(EXIT_FAILURE);
    }
}

void preencher_vetor(int *vetor, int n, int min, int max, int seed_offset) {
    srand(time(0) + seed_offset);
    for (int i = 0; i < n; i++) {
        vetor[i] = min + rand() % (max - min + 1);
    }
}

void imprimir_vetor(const int *vetor, int n) {
    for (int i = 0; i < n; i++) {
        if ((i % 10) == 0) { printf("\n"); }
        printf(GREEN NEGRITO "%d " RESET, vetor[i]);
    }
}


//=======================================================================================================================
DWORD WINAPI testar_algoritmo(LPVOID args) {
    ArgsIteratctive* argumentos = (ArgsIteratctive*)args;
    int *vetor = NULL;
    clock_t inicio, fim;
    alocar_vetor(&vetor, argumentos->n);
    preencher_vetor(vetor, argumentos->n, 0, argumentos->n * 10, argumentos->vetor);
    unsigned long comparacoes = 0, trocas = 0;

    inicio = clock();
    argumentos->func(vetor, argumentos->n, &comparacoes, &trocas);
    fim = clock();
    unsigned long duracao = (fim - inicio) * 1000 / CLOCKS_PER_SEC;

    argumentos->comparacoes = comparacoes;
    argumentos->trocas = trocas;
    argumentos->duracao = duracao;

    printf(NEGRITO RED "EXECUTANDO" RESET " | vetor %d | " CYAN "%lu" RESET " ms | " CYAN "%lu " RESET "comparacoes | " CYAN "%lu " RESET "trocas.\n", (argumentos->vetor), argumentos->duracao, argumentos->comparacoes, argumentos->trocas);
    printf(YELLOW NEGRITO "==============================================================" RESET);
    // imprimir_vetor(vetor, argumentos->n);
    printf("\n");

    free(vetor);
    return 0;
}

void executar_teste(int tamanho, void (*func1)(int*, int,  unsigned long*, unsigned long*), void (*func2)(int*, int, unsigned long*, unsigned long*), const char* nome_func1, const char* nome_func2) {
    ArgsIteratctive args, args2;
    
    args.func = func1;
    args2.func = func2;
    args.n = tamanho;
    args2.n = tamanho;
    args.max = 0,args.min= ULONG_MAX;
    args2.max = 0,args2.min= ULONG_MAX;

    unsigned long total_duracao_original = 0, total_duracao_modificado = 0;
    unsigned long total_diferenca_tempo_original = 0, total_diferenca_tempo_modificado = 0;
    unsigned long total_comparacoes_original = 0, total_comparacoes_modificado = 0;
    unsigned long total_trocas_original = 0, total_trocas_modificado = 0;

    printf(CYAN NEGRITO "\n\n-----------------------------------------------------------------------\n" RESET);
    printf(CYAN NEGRITO "                    TESTANDO FUNCAO ORIGINAL \n" RESET);
    printf(CYAN NEGRITO "-----------------------------------------------------------------------\n" RESET);

    for (int j = 0; j < 10; j++) {
        args.vetor = j; 
        unsigned long duracoes[10],comparacoes_total = 0, trocas_total = 0,diferenca_duracao = 0;
        unsigned long soma_duracao = 0;

        for (int i = 0; i < 10; i++) {
            HANDLE thread = CreateThread(NULL, 0, testar_algoritmo, &args, 0, NULL);
            WaitForSingleObject(thread, INFINITE);
            CloseHandle(thread);

            duracoes[i] = args.duracao;
            comparacoes_total += args.comparacoes;
            trocas_total += args.trocas;
            if (duracoes[i] < args.min) args.min = duracoes[i];
            if (duracoes[i] > args.max) args.max = duracoes[i];
            soma_duracao += duracoes[i];
        }
        diferenca_duracao = args.max - args.min;
        total_duracao_original += soma_duracao / 10;
        total_comparacoes_original += comparacoes_total / 10;
        total_trocas_original += trocas_total / 10;
        total_diferenca_tempo_original += diferenca_duracao;
    }

    unsigned long media_diferenca_tempo_original = total_diferenca_tempo_original / 10;

    printf(CYAN NEGRITO "\n\n-----------------------------------------------------------------------\n" RESET);
    printf(CYAN NEGRITO "                   TESTANDO FUNCAOO " MAGENTA "MODIFICADA \n" RESET);
    printf(CYAN NEGRITO "-----------------------------------------------------------------------\n" RESET);


    for (int j = 0; j < 10; j++) {
        args2.vetor = j;
        unsigned long duracoes[10];
        unsigned long comparacoes_total = 0, trocas_total = 0;
        unsigned long diferenca_duracao = 0;
        unsigned long soma_duracao = 0;

        for (int i = 0; i < 10; i++) {
            HANDLE thread2 = CreateThread(NULL, 0, testar_algoritmo, &args2, 0, NULL);
            WaitForSingleObject(thread2, INFINITE);
            CloseHandle(thread2);

            duracoes[i] = args2.duracao;
            comparacoes_total += args2.comparacoes;
            trocas_total += args2.trocas;
             if (duracoes[i] < args.min) args.min = duracoes[i];
            if (duracoes[i] > args.max) args.max = duracoes[i];
            soma_duracao += duracoes[i];
        }
        diferenca_duracao = args.max - args.min;
        total_duracao_modificado += soma_duracao / 10;
        total_comparacoes_modificado += comparacoes_total / 10;
        total_trocas_modificado += trocas_total / 10;
        total_diferenca_tempo_modificado += diferenca_duracao;
    }
    unsigned long media_diferenca_tempo_modificado = total_diferenca_tempo_modificado / 10;

    printf("\n" NEGRITO "RESULTADO DE TESTE DOS ALGORITMOS " MAGENTA ITALIC "%s" RESET NEGRITO " E " MAGENTA ITALIC "%s" RESET NEGRITO " COM " GREEN "%d " RESET NEGRITO " ELEMENTOS\n", nome_func1, nome_func2, tamanho);
    printf("|" CYAN "---------------------------------------------------------------------------------------------------------------------" RESET "|\n");
    printf("| " CYAN ITALIC "ALGORITMO" RESET "  |" CYAN ITALIC "TAMANHO DO VETOR" RESET "  |  " CYAN ITALIC "MEDIA DO TEMPO" RESET "  |  " CYAN ITALIC "DIFERE MIN E MAX" RESET "  | " CYAN ITALIC "MEDIA DE COMPARACOES" RESET " |  " CYAN ITALIC "MEDIA DE TROCAS" RESET "  |\n");
    printf("|" CYAN "---------------------------------------------------------------------------------------------------------------------" RESET "|\n");
    printf("| original   |     " GREEN NEGRITO "%d" RESET "        |       " GREEN NEGRITO "%lu" RESET "         |          " GREEN NEGRITO "%lu" RESET "         |        " GREEN NEGRITO "%lu" RESET "       |      " GREEN NEGRITO "%lu" RESET "      |\n",
           tamanho, total_duracao_original / 10, media_diferenca_tempo_original, total_comparacoes_original / 10, total_trocas_original / 10);
    printf("|" CYAN "----------------------------------------------------------------------------------------------------------------------------" RESET "|\n");
    printf("| modificada |     " GREEN NEGRITO "%d" RESET "        |       " GREEN NEGRITO "%lu" RESET "         |          " GREEN NEGRITO "%lu" RESET "         |        " GREEN NEGRITO "%lu" RESET "       |      " GREEN NEGRITO "%lu" RESET "      |\n",
           tamanho, total_duracao_modificado / 10, media_diferenca_tempo_modificado, total_comparacoes_modificado / 10, total_trocas_modificado / 10);
    printf("|" CYAN "---------------------------------------------------------------------------------------------------------------------" RESET "|\n\n\n");
}
