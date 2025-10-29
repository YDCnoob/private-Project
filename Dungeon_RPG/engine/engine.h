
#ifndef ENGINE_H
#define ENGINE_H

// Allow building with both MSVC (scanf_s, fopen_s, fscanf_s) and MinGW/GCC.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

#if !defined(_MSC_VER) && !defined(__MINGW32__)
    #define scanf_s scanf
    typedef int errno_t;
    static inline errno_t fopen_s(FILE** f, const char* name, const char* mode) {
        *f = fopen(name, mode);
        return (*f == NULL);
    }
    #define fscanf_s fscanf
#endif

#define MAX_SKILLS 3
#define NIGHT_HP_MULT 1.5
#define NIGHT_DAM_MULT 1.8
#define NIGHT_EXP_MULT 2.0
#define NIGHT_GOLD_MULT 2.0
#define MAX_SLOT 10

#include "skill.h"
#include "monster.h"
#include "character.h"
#include "battle.h"
#include "town.h"
#include "save.h"
#include "utils.h"

#endif
