#ifndef LIONKING_DIFFICULTY_H
#define LIONKING_DIFFICULTY_H

typedef enum {
    ENGINE_DIFFICULTY_EASY,
    ENGINE_DIFFICULTY_NORMAL,
    ENGINE_DIFFICULTY_HARD
} ENGINE_DIFFICULTY;

static inline int engine_difficulty_counts(ENGINE_DIFFICULTY difficulty,
    unsigned char *lives, unsigned int *continues)
{
    if (!lives || !continues) return -1;
    switch (difficulty) {
    case ENGINE_DIFFICULTY_EASY: *lives = 9; *continues = 3; return 0;
    case ENGINE_DIFFICULTY_NORMAL: *lives = 3; *continues = 1; return 0;
    case ENGINE_DIFFICULTY_HARD: *lives = 1; *continues = 0; return 0;
    }
    return -1;
}

#endif
