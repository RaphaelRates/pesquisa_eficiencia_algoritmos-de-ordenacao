
// ============================= MISSÂO DESSE PROJETO =============================

//  Medir o quão eficiente é uma variasão em relação a implementações originais de
//  certos algoritmos de ornedação. Seguindo os seguntes passos em ordem.

//  # 1º Escolher dois algoritmos de ordenação entre os algoritmos abaixo

//         (BubbleSort, MergeSort,InsertSort, insertionSort, QuickSort)

//       Após isso, perguntar a algum modelo de LLM (CHATGPT LLHAMA, COPILOT, BING)
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

    boxLoadingAnimation(80);
    // executar_teste(10, bubblesort, bubblesortM, "bubble", "buibble");
    // executar_teste(100, bubblesort, bubblesortM, "bubble", "buibble");
    // executar_teste(1000, bubblesort, bubblesortM, "bubble", "buibble");
    // executar_teste(10000, bubblesort, bubblesortM, "bubble", "buibble");

    // executar_teste(10, bubblesort, bubblesortM, "bubble", "buibble");
    // executar_teste(100, bubblesort, bubblesortM, "bubble", "buibble");
    // executar_teste(1000, bubblesort, bubblesortM, "bubble", "buibble");
    executar_teste(10000, insertionSort, insertionSortM, "insertion", "insertion modificaded");
    


    return 0;
}
