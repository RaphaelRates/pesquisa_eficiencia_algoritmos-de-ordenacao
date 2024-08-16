#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <windows.h>

//================================== ORDENAÇÕES ===================================
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
void bubblesort(int *vet, int n, int *trocas, int *comparacoes){
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
void selectionSort(int *vet, int n, int *trocas, int *comparacoes){
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
void insertionSort(int *vet, int n, int *trocas, int *comparacoes){
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
void merge(int* vet, int inicio, int meio, int fim, int *trocas, int *comparacoes){
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
void mergeSort(int *vet, int inicio, int fim, int *trocas, int *comparacoes){
    int meio;
    if(inicio < fim){
        meio = (inicio + fim)/2;
        mergeSort(vet, inicio, meio, trocas, comparacoes);
        mergeSort(vet, meio+1, fim, trocas, comparacoes);
        merge(vet, inicio, meio, fim, trocas, comparacoes);
    }
}
int particiona(int *vet, int inicio, int fim, int *trocas, int *comparacoes){
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
void quickSort(int *vet, int inicio, int fim, int *trocas, int *comparacoes){
    int pivo;
    if(fim > inicio){
        pivo = particiona(vet, inicio, fim, trocas, comparacoes);
        quickSort(vet, inicio, pivo-1, trocas, comparacoes);
        quickSort(vet, pivo+1, fim, trocas, comparacoes);
    }
}
//================================== STRUCTURES ===================================

typedef struct {
    void (*func)(int *, int);
    int n;
    unsigned long int duracao;
    BOOL recursive;
} ArgsBubble;

typedef struct {
    void (*func)(int *, int, int);
    int n;
    unsigned long int duracao;
    BOOL recursive;
} ArgsRecursive;

//================================== VETORES ===================================
void alocar_vetor(int **vetor, int n) {
    if (n > 0) {
        *vetor = (int *)malloc(n * sizeof(int));
        if (*vetor == NULL) {
            printf("ERROR: Falha na alocação de memória.\n");
            exit(1);
        }
    } else {
        printf("ERROR: Número de alocação inválido.\n");
    }
}
void preencher_vetor(int *vetor, int n, int min, int max) {
    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        vetor[i] = min + rand() % (max - min + 1);
    }
}
void imprimir_vetor(int *vetor, int n) {
    for (int i = 0; i < n; i++) { 
        printf("%d ", vetor[i]);
    }
    printf("\n");
}


DWORD WINAPI testar_algoritmo(LPVOID args) {
    ArgsBubble* argumentos;
    clock_t inicio, fim;
    unsigned long int duracao;
    int *vetor = NULL, n;

    BOOL recursive = ((ArgsBubble*)args)->recursive;

    if (!recursive) {
        argumentos = (ArgsBubble*)args;
        void (*func)(int *, int) = argumentos->func;
        n = argumentos->n;

        alocar_vetor(&vetor, n);
        if (vetor == NULL) {
            fprintf(stderr, "Falha na alocação de memória.\n");
            return 1;  
        }

        preencher_vetor(vetor, n, 0, n * 10);  
        inicio = clock();

        func(vetor, n); 

        fim = clock();
        argumentos->duracao = (fim - inicio) * 1000 / CLOCKS_PER_SEC;
        printf("Executado em %lu ms.\n", argumentos->duracao);

    } else {
        ArgsRecursive* argumentosRec = (ArgsRecursive*)args;
        void (*func)(int *, int, int) = argumentosRec->func;
        n = argumentosRec->n;

        alocar_vetor(&vetor, n);
        if (vetor == NULL) {
            fprintf(stderr, "Falha na alocação de memória.\n");
            return 1;  
        }

        preencher_vetor(vetor, n, 0, n * 10); 
        inicio = clock();

        func(vetor, 0, n - 1);

        fim = clock();
        argumentosRec->duracao = (fim - inicio) *1000 / CLOCKS_PER_SEC; 
        printf("Executado em %lu ms.\n", argumentosRec->duracao);
    }

    free(vetor); 
    return 0;
}

//==================================FUNÇÕES TESTE==========================================
void insertionSort(int *vet, int n) {
    for (int i = 1; i < n; i++) {
        int aux = vet[i];
        int j = i - 1;

        // Use um loop for para simplificar a condição de parada
        for (; j >= 0 && vet[j] > aux; j--) {
            vet[j + 1] = vet[j];
        }

        vet[j + 1] = aux;
    }
}