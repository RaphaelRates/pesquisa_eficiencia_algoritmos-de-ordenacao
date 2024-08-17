#ifndef MEU_ARQUIVO_H
#define MEU_ARQUIVO_H

void alocar_vetor(int **vetor, int n);
void percorrer_vetor(int *vetor,int n);
void imprimir_vetor(const int *vetor, int n);

#include <windows.h>
//================================== STRUCTURES ===================================

typedef struct {
    void (*func)(int *, int, unsigned long *, unsigned long *);
    int n;
    unsigned long int duracao;
    unsigned long int comparacoes;
    unsigned long int trocas;
    BOOL recursive;
    int loop;
} ArgsIteratctive;

typedef struct {
    void (*func)(int *, int, int, unsigned long *, unsigned long *);
    int n;
    unsigned long int duracao;
    unsigned long int comparacoes;
    unsigned long int trocas;
    BOOL recursive;
    int loop;
} ArgsRecursive;

#endif