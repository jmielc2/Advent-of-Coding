#include <stdio.h>
#include <string.h>

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

void getline(FILE* file, char* buf) {
    memset(buf, '\0', sizeof(char) * 8);
    char a = 'a';
    int i = 0;
    while (a != '\n') {
        if (EOF != (a = getc(file))) {
            buf[i] = a;
        } else {
            break;
        }
        i++;
    }
} 

int main(int argc, char* argv[]) {
    char *filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
        return -1;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open '%s'.\n", filename);
        return -1;
    }

    char input[8];
    int round, score = 0;
    while (!feof(file)) {
        round = 0;
        getline(file, input);
        if (strcmp("", input) == 0) {
            continue;
        }
        int opp = input[0] - 'A' + 1;
        switch (input[2]) {
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
    return 0;
}