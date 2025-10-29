
#include "../engine/engine.h"
#include "story.h"
#include <windows.h>

int main(void) {
    SetConsoleOutputCP(65001);   // 콘솔 출력을 UTF-8로
    SetConsoleCP(65001);         // 입력도 UTF-8로

    srand((unsigned)time(NULL));

    CHARACTER character;
    MOP mop[3] = {
        {"슬라임", 150, 150, 50, 50, 50, 50, 100, 100},
        {"임프",   250, 250, 70, 70, 70, 70, 150, 150},
        {"고블린", 300, 300, 80, 80, 80, 80, 250, 250}
    };
    int dun_lev = 1;

    showIntro();
    showMainMenu(&character, mop, &dun_lev);
    return 0;
}
