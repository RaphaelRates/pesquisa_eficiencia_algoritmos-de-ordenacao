#ifndef MEU_ARQUIVO_H
#define MEU_ARQUIVO_H

void alocar_vetor(int **vetor, int n);
void percorrer_vetor(int *vetor,int n);
void imprimir_vetor(const int *vetor, int n);

#include <windows.h>
//================================== STRUCTURES ===================================
typedef void (*FuncaoIterativa)(int*, int, unsigned long*, unsigned long*);
typedef void (*FuncaoRecursiva)(int*, int,int, unsigned long*, unsigned long*);

typedef struct {
    FuncaoIterativa func;
    int n;
    unsigned long int duracao;
    unsigned long int comparacoes;
    unsigned long int trocas;
    int max;
    int min;
    int vetor;
} ArgsIteratctive;

typedef struct {
    FuncaoRecursiva func;
    int n;
    unsigned long int duracao;
    unsigned long int comparacoes;
    unsigned long int trocas;
    int max;
    int min;
    int vetor;
} ArgsRecursive;

#endif