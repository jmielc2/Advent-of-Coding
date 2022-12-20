#include "../include/ctools.h"

int main(int argc, char* argv[]) {
    char *filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s | <filename>\n", argv[0]);
        return -1;
    }

    FILE* infile = fopen(filename, "r");
    if (!infile) {
        fprintf(stderr, "Error: Failed to open '%s'.", filename);
        return -1;
    }

    int max[3];
    int sum = 0;
    string input = initString();
    memset(&max, 0, sizeof(int) * 3);
    while (!feof(infile)) {
        if (!getline(infile, &input)) {
            fprintf(stderr, "Error: getline function failed.\n");
            return -1;
        }
        if (!strcmp(input.buf, "\0")) {
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
            sum += atoi(input.buf);
        }
    }
    fclose(infile);

    sum = 0;
    printf("Top Three Elves:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d.) %d\n", 3 - i, max[i]);
        sum += max[i];
    }
    printf("\nTotal: %d\n", sum);
    destroyString(&input);
    return 0;
}