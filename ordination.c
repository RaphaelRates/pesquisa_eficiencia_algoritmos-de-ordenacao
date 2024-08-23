#include <stdlib.h>
#include <math.h>

//================================== SWAP ===================================
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

//=======================================  BUBBLE SORT =======================================  
void bubblesort(int *vet, int n, unsigned long *comparacoes, unsigned long *trocas){
    int i, mudou, fim = n-1;
    *trocas = 0;
    *comparacoes = 0;
    do{
        mudou = 0;
        for(i = 0; i < fim; i++){
            (*comparacoes)++;
            if(vet[i] > vet[i+1]){
                swap(&vet[i], &vet[i+1]);
                mudou = 1;
                (*trocas)++;
            }
        }
        fim--;
    }while(mudou);
}

//=======================================  SELECTION SORT =======================================  
void selectionSort(int *vet, int n,unsigned long *comparacoes, unsigned long *trocas){
    int i, j, menor;
    *trocas = 0;
    *comparacoes = 0;
    for(i = 0; i < n-1; i++){
        menor = i;
        for(j = i+1; j < n; j++){
            (*comparacoes)++;
            if(vet[j] < vet[menor]){
                menor = j;
            }
        }
        if(i != menor){
            swap(&vet[i], &vet[menor]);
            (*trocas)++;
        }
    }
}
//=======================================  INSERTION SORT =======================================  
void insertionSort(int *vet, int n, unsigned long *comparacoes, unsigned long *trocas){
    int i, j, aux;
    *trocas = 0;
    *comparacoes = 0;
    for(i = 1; i < n; i++){
        aux = vet[i];
        j = i;
        while(j > 0 && aux < vet[j-1]){
            (*comparacoes)++;
            vet[j] = vet[j-1];
            j--;
            (*trocas)++;
        }
        vet[j] = aux;
        if (j != i) {
            (*trocas)++;
        }
    }
}
//=======================================  MERGE HELPER =======================================  
void merge(int* vet, int inicio, int meio, int fim,unsigned long *comparacoes, unsigned long *trocas){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim-inicio +1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int*) malloc(tamanho * sizeof(int));
    if(temp != NULL){
        for(i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                (*comparacoes)++;
                if(vet[p1]< vet[p2]){
                    temp[i] = vet[p1];
                    p1++;
                }else{
                    temp[i] = vet[p2];
                    p2++;
                }
                if(p1>meio){
                    fim1 = 1;
                }
                if(p2>fim){
                    fim2 = 1;
                }
            }else{
                if(!fim1){
                    temp[i] = vet[p1];
                    p1++;
                }else{
                    temp[i] = vet[p2];
                    p2++;
                }
            }
        }
        for(j = 0, k = inicio; j < tamanho; j++, k++){
            vet[k] = temp[j];
            (*trocas)++;
        }
    }
    free(temp);
}

//=======================================  MERGE SORT =======================================  
void mergeSort(int *vet, int inicio, int fim, unsigned long *comparacoes, unsigned long *trocas){
        int meio;
    if(inicio < fim){
        meio = (inicio + fim)/2;
        mergeSort(vet, inicio, meio, comparacoes, trocas);
        mergeSort(vet, meio+1, fim, comparacoes, trocas);   
        merge(vet, inicio, meio, fim, comparacoes, trocas);
    }
}

//======================================= QUICK HELPER =======================================  
int particiona(int *vet, int inicio, int fim, unsigned long *comparacoes, unsigned long *trocas){
    int esq, dir, pivo;
    esq = inicio;
    dir = fim;
    pivo = vet[inicio];
    while(esq < dir){
        while(esq <= fim && vet[esq] <= pivo){
            esq++;
            (*comparacoes)++;
        }
        while(dir >= inicio && vet[dir] > pivo){
            dir--;
            (*comparacoes)++;
        }
        if(esq < dir){
            swap(&vet[esq], &vet[dir]);
            (*trocas)++;
        }
    }
    swap(&vet[inicio], &vet[dir]);
    (*trocas)++;
    return dir;
}

//=======================================  QUICK SORT =======================================  
void quickSort(int *vet, int inicio, int fim, int unsigned long *comparacoes, unsigned long *trocas){
    int pivo;
    if(fim > inicio){
        pivo = particiona(vet, inicio, fim, trocas, comparacoes);
        quickSort(vet, inicio, pivo-1, trocas, comparacoes);
        quickSort(vet, pivo+1, fim, trocas, comparacoes);
    }
}

//=============================================================================
void bubblesortM(int *vet, int n, unsigned long *comparacoes, unsigned long *trocas) {
    int i, mudou;
    *trocas = 0;
    *comparacoes = 0;
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (i = 0; i <= n - 2; i += 2) {
            (*comparacoes)++;
            if (vet[i] > vet[i + 1]) {
                swap(&vet[i], &vet[i + 1]);
                sorted = 0;
                (*trocas)++;
            }
        }
        for (i = 1; i <= n - 2; i += 2) {
            (*comparacoes)++;
            if (vet[i] > vet[i + 1]) {
                swap(&vet[i], &vet[i + 1]);
                sorted = 0;
                (*trocas)++;
            }
        }
    }
}


