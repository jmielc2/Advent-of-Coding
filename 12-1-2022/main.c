#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void getline(FILE* file, char* buf) {
    memset(buf, '\0', sizeof(buf));
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
    buf[i - 1] = '\0';
}

int main() {
    FILE* infile = fopen("input.txt", "r");
    if (!infile) {
        fprintf(stderr, "Error: Failed to open input.txt.");
        return -1;
    }

    int max[3];
    int sum = 0;
    char input[128];

    memset(&max, 0, sizeof(int) * 3);
    while (!feof(infile)) {
        getline(infile, input);
        if (!strcmp(input, "\0")) {
            for (int i = 0; i < 3; i++) {
                if (max[i] > sum) {
                    break;
                } else if (i) {
                    max[i - 1] = max[i];
                }
                max[i] = sum;
            }
            sum = 0;
        } else {
            sum += atoi(input);
        }
    }

    sum = 0;
    printf("Top Three Elves:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d.) %d\n", 3 - i, max[i]);
        sum += max[i];
    }
    printf("\nTotal: %d\n", sum);
    return 0;
}