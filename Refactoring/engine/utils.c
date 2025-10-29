
#include "engine.h"

void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

int clampHP(int hp) { return hp < 0 ? 0 : hp; }

int clampAndCheckDeath(int* hp) {
    if (*hp <= 0) { *hp = 0; return 1; }
    return 0;
}

void waitForKeyPress() {
    printf("계속하려면 Enter 또는 Spacebar를 누르세요...");
    Sleep(300);
    while (1) {
        int key = _getch();
        if (key == ' ' || key == 13) break;
    }
    printf("\n");
}

void getCurrentDate(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d", t);
}
