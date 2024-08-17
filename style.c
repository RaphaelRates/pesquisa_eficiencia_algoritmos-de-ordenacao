
#include "style.h"
#include <stdio.h>

void boxLoadingAnimation(int duration) {
    const char *frames[] = {
        "[    ]",
        "["GREEN"=   "RESET"]",
        "["GREEN"==  "RESET"]",
        "["GREEN"=== "RESET"]",
        "["GREEN"===="RESET"]",
        "["GREEN" ==="RESET"]",
        "["GREEN"  =="RESET"]",
        "["GREEN"   ="RESET"]",
    };
    int i = 0;
    while (duration > 0) {
        printf("\r%s", frames[i]);
        fflush(stdout);
        Sleep(80);
        i = (i + 1) % 8;
        duration--;
    }
    printf("\r[====] Done!\n");
}