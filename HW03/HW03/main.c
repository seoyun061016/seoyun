#include <stdio.h>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void moveCursor(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
}

void printBomb(int isExploded)
{
    if (isExploded)
    {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else
    {
        printf("(  b  )");
    }
}

static int enableVirtualTerminal(void)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return 0;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return 0;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return 0;

    return 1;
}

int main(void)
{
    enableVirtualTerminal();

    
    const int bombX = 2;
    const int bombY = 1;

    
    const int path[][2] = {
        {14,9}, 
        {14,8},{14,7},{14,6},{14,5},{14,4},{14,3},
        {13,3},{12,3},{11,3},
        {11,4},{11,5},{11,6},{11,7},
        {12,7},{13,7},
        {13,6},{13,5},
        {12,5},
        {12,4},
        {12,3}, 
        {11,3},{10,3},{9,3},{8,3},{7,3},
        {7,4},{7,5},{7,6},{7,7},{7,8},{7,9},
        {8,9},{9,9},{10,9},{11,9},{12,9},{13,9},{14,9}, 
        {14,8},{14,7},{14,6},{14,5},{14,4},{14,3},{14,2},{14,1},
        {13,1},{12,1},{11,1},{10,1},{9,1},{8,1},{7,1},{6,1},{5,1},{4,1},
        {3,1},{2,1} 
    };
    const int pathLen = (int)(sizeof(path) / sizeof(path[0]));

    
    for (int i = 0; i < pathLen; ++i) {
        moveCursor(path[i][0], path[i][1]);
        printf("#");
    }
    fflush(stdout);

    
    moveCursor(bombX, bombY);
    printBomb(0);
    fflush(stdout);

    
    for (int i = 0; i < pathLen; ++i) {
        moveCursor(path[i][0], path[i][1]);
        printf("*");
        fflush(stdout);
        Sleep(200);

        if (i < pathLen - 1) {
            moveCursor(path[i][0], path[i][1]);
            printf(" ");
            fflush(stdout);
        }
    }

    
    moveCursor(bombX, bombY);
    printBomb(1);
    fflush(stdout);

    moveCursor(1, 25);
    fflush(stdout);

    return 0;
}
