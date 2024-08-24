#ifndef ORDENACAO_H
#define ORDENACAO_H

void swap(int *x, int *y);
void bubblesort(int *vet, int n, unsigned long *trocas, unsigned long *comparacoes);
void selectionSort(int *vet, int n,unsigned long *trocas, unsigned long *comparacoes);
void insertionSort(int *vetor, int n, unsigned long *comparacoes, unsigned long *trocas);
void mergeSort(int *vet, int, int n,unsigned long *trocas, unsigned long *comparacoes);
void quickSort(int *vet, int, int n,unsigned long *trocas, unsigned long *comparacoes);

//++++++++++++++++++++++++++++++++++MODIFICADOS+++++++++++++++++++++++++++++++++
void bubblesortM(int *vet, int n, unsigned long *trocas, unsigned long *comparacoes);
void insertionSortM(int *vet, int n, unsigned long *comparacoes, unsigned long *trocas);

#endif