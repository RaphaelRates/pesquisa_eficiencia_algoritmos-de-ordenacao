
#include "style.h"
#include <Windows.h>
#include <stdio.h>

void boxLoadingAnimation(int duration) {
    const char *frames[] = {
        "[         ]",
        "["GREEN"=        "RESET"]",
        "["GREEN"==       "RESET"]",
        "["GREEN"===      "RESET"]",
        "["GREEN"====     "RESET"]",
        "["GREEN"=====    "RESET"]",
        "["GREEN"======   "RESET"]",
        "["GREEN"======== "RESET"]",
        "["GREEN"========="RESET"]",
        "["GREEN" ========"RESET"]",
        "["GREEN"  ======="RESET"]",
        "["GREEN"   ======"RESET"]",
        "["GREEN"    ====="RESET"]",
        "["GREEN"     ===="RESET"]",
        "["GREEN"      ==="RESET"]",
        "["GREEN"       =="RESET"]",
        "["GREEN"        ="RESET"]",
    };
    int i = 0;
    printf("CARREGANDO\n");
    while (duration*10 > 0) {
        printf("\r%s", frames[i]);
        fflush(stdout);
        Sleep(30);
        i = (i + 1) % 17;
        duration--;
    }
    printf("\r[====] Done!\n");
}