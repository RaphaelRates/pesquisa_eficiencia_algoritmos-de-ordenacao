
// ============================= MISSÂO DESSE PROJETO =============================

//  Medir o quão eficiente é uma variasão em relação a implementações originais de
//  certos algoritmos de ornedação. Seguindo os seguntes passos em ordem.

//  # 1º Escolher dois algoritmos de ordenação entre os algoritmos abaixo

//         (BubbleSort, MergeSort,InsertSort, SelectionSort, QuickSort)

//       Após isso, perguntar a algum modelo de LM (CHATGPT LLHAMA, COPILOT, BING)
//     como tornar tal algoritmo mais eficiente, em seguinda testá-los e fazer uma 
//     análise crítica sobre tais alterações e escolher uma variação para cada codigo
//     JUSTIFICANDO A SUA ESCOLHA!!!

//  # 2º Para cada algoritmo, compare a sua complexidade por analise de comportamento 
//    assintotico usando a notação Big(O).
//    Depois faz uma analise empirica, implementando um gerador de inteiros aleatorias
//    podendo retornar um vetor de tamanho N (10,100,1.000,10.000)

#include "biblioteca.c"
#include "ordination.h"
#include "ordination.c"

int main() {

    executar_teste(10, bubblesort, selectionSort, "bubbleSort", "selectionSort");
    executar_teste(100, bubblesort, selectionSort, "bubbleSort", "selectionSort");
    executar_teste(1000, bubblesort, selectionSort, "bubbleSort", "selectionSort");
    executar_teste(10000, bubblesort, selectionSort, "bubbleSort", "selectionSort");

    executar_teste(10, bubblesort, insertionSort, "bubbleSort", "insertionSort");
    executar_teste(100, bubblesort, insertionSort, "bubbleSort", "insertionSort");
    executar_teste(1000, bubblesort, insertionSort, "bubbleSort", "insertionSort");
    executar_teste(10000, bubblesort, insertionSort, "bubbleSort", "insertionSort");

    return 0;
}
