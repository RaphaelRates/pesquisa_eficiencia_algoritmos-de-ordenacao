#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "biblioteca.h"
#include "ordination.h"
#include "style.h"

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

void testar_algoritmo(ArgsIteratctive* args, int* elements) {
    clock_t inicio, fim;
    unsigned long comparacoes = 0, trocas = 0;

    inicio = clock();
    args->func(elements, args->n, &comparacoes, &trocas);
    fim = clock();
    unsigned long duracao = (fim - inicio) * 1000 / CLOCKS_PER_SEC;

    args->comparacoes = comparacoes;
    args->trocas = trocas;
    args->duracao = duracao;
    
    printf("\n" NEGRITO RED "EXECUTANDO" RESET " | vetor %d |  " CYAN "%lu " RESET "ms | " RED "%d " RESET " - " GREEN "%d" RESET " = " MAGENTA "%d" RESET " | " CYAN "%lu " RESET "comparacoes | " CYAN "%lu " RESET "trocas.\n",
           args->vetor, args->duracao, args->max, args->min, args->max - args->min, args->comparacoes, args->trocas);
    printf(YELLOW NEGRITO "==============================================================" RESET);
}

void executar_teste(int tamanho, FuncaoIterativa func1, FuncaoIterativa func2, const char* nome_func1, const char* nome_func2) {
    ArgsIteratctive args, args2;
    args.func = func1;
    args2.func = func2;
    args.n = tamanho;
    args2.n = tamanho;
    args.min = ULONG_MAX; args.max = 0;
    args2.min = ULONG_MAX;args2.max = 0;

    unsigned long total_duracao_original = 0, total_duracao_modificado = 0;
    unsigned long duracao_min_original = ULONG_MAX, duracao_max_original = 0;
    unsigned long total_comparacoes_original = 0, total_comparacoes_modificado = 0;
    unsigned long duracao_min_modificado = ULONG_MAX, duracao_max_modificado = 0;
    unsigned long total_trocas_original = 0, total_trocas_modificado = 0;

    for (int j = 0; j < 10; j++) {
        int *elements = NULL, *elements_copia = NULL;
        alocar_vetor(&elements, tamanho);
        alocar_vetor(&elements_copia, tamanho);

        preencher_vetor(elements, tamanho, 0, tamanho * 10, j);
        memcpy(elements_copia, elements, tamanho * sizeof(int));
        args.vetor = j + 1;
        args2.vetor = j + 1;

        printf(CYAN NEGRITO "\n\n-----------------------------------------------------------------------\n" RESET);
        printf(CYAN NEGRITO "                    TESTANDO FUNCAO ORIGINAL \n" RESET);
        printf(CYAN NEGRITO "-----------------------------------------------------------------------" RESET);

        unsigned long comparacoes_total_original = 0, trocas_total_original = 0;
        unsigned long soma_duracao_original = 0;

        for (int i = 0; i < 10; i++) {
            testar_algoritmo(&args, elements_copia);
            soma_duracao_original += args.duracao;
            comparacoes_total_original += args.comparacoes;
            trocas_total_original += args.trocas;

            if (args.duracao < duracao_min_original) {
                duracao_min_original = args.duracao;
                args.min = duracao_min_original;
            }
            if (args.duracao > duracao_max_original) {
                duracao_max_original = args.duracao;
                args.max = duracao_max_original;
            }

            memcpy(elements_copia, elements, tamanho * sizeof(int));
        }

        total_duracao_original += soma_duracao_original / 10;
        total_comparacoes_original += comparacoes_total_original / 10;
        total_trocas_original += trocas_total_original / 10;

        printf(CYAN NEGRITO "\n\n-----------------------------------------------------------------------\n" RESET);
        printf(CYAN NEGRITO "                   TESTANDO FUNCAO " MAGENTA "MODIFICADA \n" RESET);
        printf(CYAN NEGRITO "-----------------------------------------------------------------------\n" RESET);

        unsigned long comparacoes_total_modificado = 0, trocas_total_modificado = 0;
        unsigned long soma_duracao_modificado = 0;

        for (int i = 0; i < 10; i++) {
            testar_algoritmo(&args2, elements_copia);
            soma_duracao_modificado += args2.duracao;
            comparacoes_total_modificado += args2.comparacoes;
            trocas_total_modificado += args2.trocas;

            if (args2.duracao < duracao_min_modificado) {
                duracao_min_modificado = args2.duracao;
                args2.min = duracao_min_modificado;
            }
            if (args2.duracao > duracao_max_modificado) {
                duracao_max_modificado = args2.duracao;
                args2.max = duracao_max_modificado;
            }
            memcpy(elements_copia, elements, tamanho * sizeof(int));
        }

        total_duracao_modificado += soma_duracao_modificado / 10;
        total_comparacoes_modificado += comparacoes_total_modificado / 10;
        total_trocas_modificado += trocas_total_modificado / 10;

        free(elements);
        free(elements_copia);
    }

    // Relatório final
    printf("\n\n\n" NEGRITO "RESULTADO DE TESTE DOS ALGORITMOS " MAGENTA ITALIC "%s" RESET NEGRITO " E " MAGENTA ITALIC "%s" RESET NEGRITO " COM " GREEN "%d " RESET NEGRITO " ELEMENTOS\n", nome_func1, nome_func2, tamanho);
    printf("|" CYAN "---------------------------------------------------------------------------------------------------------------------" RESET "|\n");
    printf("| " CYAN ITALIC "ALGORITMO" RESET "  |" CYAN ITALIC "TAMANHO DO VETOR" RESET "  |  " CYAN ITALIC "MEDIA DO TEMPO" RESET "  |  " CYAN ITALIC "DIFERENÇA MIN E MAX" RESET "  | " CYAN ITALIC "MEDIA DE COMPARACOES" RESET " |  " CYAN ITALIC "MEDIA DE TROCAS" RESET "  |\n");
    printf("|" CYAN "---------------------------------------------------------------------------------------------------------------------" RESET "|\n");
    printf("| original   |     " GREEN NEGRITO "%d" RESET "        |       " GREEN NEGRITO "%lu" RESET "         |          " GREEN NEGRITO "%lu" RESET "         |        " GREEN NEGRITO "%lu" RESET "       |      " GREEN NEGRITO "%lu" RESET "      |\n",
           tamanho, total_duracao_original / 10, args.max - args.min, total_comparacoes_original / 10, total_trocas_original / 10);
    printf("|" CYAN "----------------------------------------------------------------------------------------------------------------------------" RESET "|\n");
    printf("| modificada |     " GREEN NEGRITO "%d" RESET "        |       " GREEN NEGRITO "%lu" RESET "         |          " GREEN NEGRITO "%lu" RESET "         |        " GREEN NEGRITO "%lu" RESET "       |      " GREEN NEGRITO "%lu" RESET "      |\n",
           tamanho, total_duracao_modificado / 10, args2.max - args2.min, total_comparacoes_modificado / 10, total_trocas_modificado / 10);
    printf("|" CYAN "---------------------------------------------------------------------------------------------------------------------" RESET "|\n");
}

