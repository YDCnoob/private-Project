
#include "../engine/engine.h"
#include "story.h"

int main(void) {
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
