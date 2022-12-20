#include "../include/ctools.h"

enum {A=1, B=2, C=3};
enum {X=0, Y=3, Z=6};

int getPlay(const int *opp, const int outcome) {
    int play;
    if (outcome == Z) {
        if (*opp == C) {
            play = A;
        } else {
            play = *opp + 1;
        }
    } else if (outcome == X) {
        if (*opp == A) {
            play = C;
        } else {
            play = *opp - 1;
        }
    } else {
        play = *opp;
    }
    return play + outcome;
}

int main(int argc, char* argv[]) {
    char *filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s | <filename>\n", argv[0]);
        return -1;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open '%s'.\n", filename);
        return -1;
    }

    string input = initString();
    int round, score = 0;
    while (!feof(file)) {
        round = 0;
        if (!getline(file, &input)) {
            fprintf(stderr, "Error: getline function failed.\n");
            return -1;
        }
        if (!strcmp("", input.buf)) {
            continue;
        }
        int opp = input.buf[0] - 'A' + 1;
        switch (input.buf[2]) {
        case('X'):
            round += getPlay(&opp, X);
            break;
        case('Y'):
            round += getPlay(&opp, Y);
            break;
        case('Z'):
            round += getPlay(&opp, Z);
            break;
        }
        score += round;
    }
    fclose(file);

    printf("Final Score: %d\n", score);
    destroyString(input);
    return 0;
}