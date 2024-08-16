
#include "style.h"

void printAnimation(const char *send, int time, Style style) {
    printf("%s%s", style.color, style.fontStyle);
    while (*send) {
        putchar(*send++);
        fflush(stdout);
        Sleep(time);
    }
    printf(RESET);
    putchar('\n');
}

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