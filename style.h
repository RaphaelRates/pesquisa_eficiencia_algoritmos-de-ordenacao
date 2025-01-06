#ifndef STYLE_H
#define STYLE_H

#define BLUE            "\x1b[34m"
#define MAGENTA         "\x1b[35m"
#define CYAN            "\x1b[36m"
#define RESET           "\x1b[0m"
#define NEGRITO         "\x1b[1m" 
#define DIMINUIDO       "\x1b[2m" 
#define SUBLINHADO      "\x1b[4m" 
#define ITALIC          "\e[3m"
#define MAGENTA_BG      "\x1b[45m" 
#define CYAN_BG         "\x1b[46m"
#define WHITE_BG        "\x1b[47m"
#define BLACK           "\x1b[30m"
#define RED             "\x1b[31m"
#define YELLOW          "\x1b[33m"
#define WHITE           "\x1b[37m"
#define BRIGHT_BLACK    "\x1b[90m"
#define BRIGHT_RED      "\x1b[91m"
#define BRIGHT_GREEN    "\x1b[92m"
#define BRIGHT_YELLOW   "\x1b[93m"
#define BRIGHT_BLUE     "\x1b[94m"
#define BRIGHT_CYAN     "\x1b[96m"
#define BRIGHT_WHITE    "\x1b[97m"
#define BRIGHT_BLACK_BG "\x1b[100m" 
#define BRIGHT_RED_BG   "\x1b[101m" 
#define BRIGHT_GREEN_BG "\x1b[102m" 
#define BRIGHT_YELLOW_BG "\x1b[103m" 
#define BRIGHT_BLUE_BG  "\x1b[104m" 
#define BRIGHT_MAGENTA_BG "\x1b[105m" 
#define BRIGHT_CYAN_BG  "\x1b[106m" 
#define BRIGHT_WHITE_BG "\x1b[107m" 
#define GREEN           "\x1b[32m"

void boxLoadingAnimation(int duration);

#endif