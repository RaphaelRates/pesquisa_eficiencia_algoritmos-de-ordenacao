#ifndef MEU_ARQUIVO_H
#define MEU_ARQUIVO_H
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

typedef struct{
    FuncaoRecursiva func;
    int n;
    unsigned long int duracao;
    unsigned long int comparacoes;
    unsigned long int trocas;
    int max;
    int min;
    int vetor;
} ArgsRecursive;

void alocar_vetor(int **vetor, int n);
void percorrer_vetor(int *vetor,int n);
void imprimir_vetor(const int *vetor, int n);
void testar_algoritmo(ArgsIteratctive* args, int * elements);
void executar_teste(int tamanho, FuncaoIterativa func1, FuncaoIterativa func2, const char* nome_func1, const char* nome_func2);

#endif