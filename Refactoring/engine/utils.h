
#ifndef UTILS_H
#define UTILS_H

enum ColorType {
    BLACK,
    darkBLUE,
    DarkGreen,
    darkSkyBlue,
    DarkRed,
    DarkPurple,
    DarkYellow,
    GRAY,
    DarkGray,
    BLUE,
    GREEN,
    SkyBlue,
    RED,
    PURPLE,
    YELLOW,
    WHITE
};

void textcolor(int colorNum);
int clampHP(int hp);
int clampAndCheckDeath(int* hp);
void waitForKeyPress();
void getCurrentDate(char* buffer, size_t size);

#endif
