#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "biblioteca.h"
#include <limits.h>
#include "ordination.h"
#include "style.h"

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

void preencher_vetor(int *vetor, int n, int min, int max, int seed_offset) {
    srand(time(0) + seed_offset);
    for (int i = 0; i < n; i++) {
        vetor[i] = min + rand() % (max - min + 1);
    }
}

void imprimir_vetor(const int *vetor, int n) {
    
    for (int i = 0; i < n; i++) {
        if ((i%10) == 0){printf("\n");}
        printf(GREEN NEGRITO"%d "RESET, vetor[i]);
    }
    printf("\n");
}

//=======================================================================================================================
DWORD WINAPI testar_algoritmo(LPVOID args) {
    ArgsRecursive* argumentos = (ArgsRecursive*)args;
    int *vetor = NULL;
    clock_t inicio, fim;

    alocar_vetor(&vetor, argumentos->n);
    preencher_vetor(vetor, argumentos->n, 0, argumentos->n * 10, argumentos->loop);

    argumentos->comparacoes = 0;
    argumentos->trocas = 0;

    inicio = clock();
    argumentos->func(vetor,0 ,argumentos->n -1 , &argumentos->comparacoes, &argumentos->trocas);
    fim = clock();

    argumentos->duracao = (fim - inicio) ;
    printf(YELLOW NEGRITO"==============================================================\n"RESET);
    printf(NEGRITO RED"EXECUTANDO"RESET" loop %d em "CYAN"%lu"RESET" ms, com "CYAN"%lu "RESET"comparacoes e "CYAN"%lu "RESET"trocas.", argumentos->loop, argumentos->duracao, argumentos->comparacoes, argumentos->trocas);
    imprimir_vetor(vetor, argumentos->n);
    printf(YELLOW NEGRITO"=============================================================="RESET);
    printf("\n\n");

    free(vetor);
    return 0;
}


void executar_teste(int tamanho, void (*func1)(int*, int,int, unsigned long*, unsigned long*), void (*func2)(int*, int,int, unsigned long*, unsigned long*), const char* nome_func1, const char* nome_func2) {
    ArgsRecursive args, args2;
    args.func = func1;
    args2.func = func2;
    args.n = tamanho;
    args2.n = tamanho;
    args.loop = 0;
    args2.loop = 0;
    unsigned long int total_duracao_original = 0, total_duracao_modificado = 0,min_duracao = 0, max_duracao = ULONG_MAX;
    unsigned long int total_comparacoes_original = 0, total_comparacoes_modificado = 0, total_trocas_original = 0, total_trocas_modificado = 0;

    //srand(time(0));
    // for (int i = 0; i < 10; i++) {
    //     args.loop++;
    //     args2.loop++;

    //     HANDLE thread = CreateThread(NULL, 0, testar_algoritmo, &args, 0, NULL);
    //     HANDLE thread2 = CreateThread(NULL, 0, testar_algoritmo, &args2, 0, NULL);
        
    //     WaitForSingleObject(thread, INFINITE);
    //     WaitForSingleObject(thread2, INFINITE);
        
    //     CloseHandle(thread);
    //     CloseHandle(thread2);

    //     total_duracao_original += args.duracao;
    //     total_comparacoes_original += args.comparacoes;
    //     total_trocas_original += args.trocas;

    //     total_duracao_modificado += args2.duracao;
    //     total_comparacoes_modificado += args2.comparacoes;
    //     total_trocas_modificado += args2.trocas;

    //     if (args.duracao < min_duracao) min_duracao = args.duracao;
    //     if (args.duracao > max_duracao) max_duracao = args.duracao;
    // 
    // }

     for (int i = 0; i < 10; i++) {
        args.loop++;
        HANDLE thread = CreateThread(NULL, 0, testar_algoritmo, &args, 0, NULL);
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
        
        total_duracao_original += args.duracao;
        total_comparacoes_original += args.comparacoes;
        total_trocas_original += args.trocas;

        

        if (args.duracao < min_duracao) min_duracao = args.duracao;
        if (args.duracao > max_duracao) max_duracao = args.duracao;
    }
    for (size_t i = 0; i < 10; i++)
    {
        args2.loop++;
        HANDLE thread2 = CreateThread(NULL, 0, testar_algoritmo, &args2, 0, NULL);
        WaitForSingleObject(thread2, INFINITE);
        CloseHandle(thread2);

        total_duracao_modificado += args2.duracao;
        total_comparacoes_modificado += args2.comparacoes;
        total_trocas_modificado += args2.trocas;
    }

    

    printf("\n"NEGRITO"RESULTADO DE TESTE DOS ALGORITMO "MAGENTA ITALIC"%s"RESET NEGRITO" E "MAGENTA ITALIC"%s"RESET NEGRITO" DE "GREEN"%d "RESET NEGRITO"ELEMENTOS\n", nome_func1, nome_func2, tamanho);
    printf("|"CYAN"---------------------------------------------------------------------------------------------------------------------"RESET"|");
    printf("\n| "CYAN ITALIC"ALGORITMO"RESET"  |"CYAN ITALIC"TAMANHO DO VETOR"RESET"  |  "CYAN ITALIC"MEDIA DO TEMPO"RESET"  |  "CYAN ITALIC"DIFERENCA DE TEMPO"RESET"  | "CYAN ITALIC"MEDIA DE COMPARACAO"RESET" |  "CYAN ITALIC"MEDIA DE TROCAS"RESET"  |\n");
    printf("|"CYAN"---------------------------------------------------------------------------------------------------------------------"RESET"|\n");
    printf("| original   |     "GREEN NEGRITO"%d"RESET"        |       "GREEN NEGRITO"%lu"RESET"         |          "GREEN NEGRITO"%lu"RESET"         |        "GREEN NEGRITO"%lu"RESET"       |      "GREEN NEGRITO"%lu"RESET"      |\n", tamanho, total_duracao_original / 10, max_duracao - min_duracao, total_comparacoes_original / 10, total_trocas_original / 10);
    printf("|"CYAN"----------------------------------------------------------------------------------------------------------------------------"RESET"|\n");
    printf("| modificada |     "GREEN NEGRITO"%d"RESET"        |       "GREEN NEGRITO"%lu"RESET"         |          "GREEN NEGRITO"%lu"RESET"         |        "GREEN NEGRITO"%lu"RESET"       |      "GREEN NEGRITO"%lu"RESET"      |\n", tamanho, total_duracao_modificado / 10, max_duracao - min_duracao, total_comparacoes_modificado / 10, total_trocas_modificado / 10);
    printf("|"CYAN"---------------------------------------------------------------------------------------------------------------------"RESET"|\n\n\n");
}
