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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include "biblioteca.c"

int main(){

    ArgsBubble args = {insertionSort, 1000,0, FALSE};
    ArgsBubble args2 = {insertionSort, 1000,0, FALSE};

    HANDLE thread = CreateThread(NULL,0,testar_algoritmo,&args,0,NULL);
    HANDLE thread2 = CreateThread(NULL,0,testar_algoritmo,&args2,0,NULL);

    WaitForSingleObject(thread, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    CloseHandle(thread);
    CloseHandle(thread2);

    if (args2.duracao < args.duracao) {
        printf("A thread da funcao modificada terminou mais cedo (%lu ms vs %lu ms).\n", args2.duracao, args.duracao);
    } else if (args2.duracao > args.duracao) {
        printf("A thread da funcao original terminou mais cedo (%lu ms vs %lu ms).\n", args.duracao, args2.duracao);
    } else {
        printf("As threads terminaram no mesmo tempo (%lu ms).\n", args.duracao);
    }




    return 0;
}