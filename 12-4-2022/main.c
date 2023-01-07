#include "../include/ctools.h"
#include <ctype.h>

int contains(int vals[]) {
    return (vals[0] <= vals[2] && vals[1] >= vals[3]) || (vals[0] >= vals[2] && vals[1] <= vals[3]);
}

int overlap(int vals[]) {
    return (vals[0] >= vals[2] && vals[0] <= vals[3]) || (vals[1] >= vals[2] && vals[1] <= vals[3]) || contains(vals);
}

int main(int argc, char* argv[]) {
    char* filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s | <filename>\n", argv[0]);
        return -1;
    }

    FILE* file = fopen(filename,  "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open '%s'.\n", filename);
        return -1;
    }

    int count = 0;
    string input = initString();
    while (!feof(file)) {
        if (!getline(file, &input)) {
            fprintf(stderr, "Error: getline function failed.\n");
            return -1;
        }
        if (!strcmp("", input.buf)) {
            continue;
        }
        int i = 0, j = 0;
        int vals[4];
        for (int k = 0; k < 4; k++) {
            while (isdigit(input.buf[j])) {
                j++;
            }
            string a = substr(input.buf, i, j - i);
            vals[k] = atoi(a.buf);
            j++;
            i = j;
            destroyString(&a);
        }
        if (overlap(vals)) {
            count++;
        }
    }
    fclose(file);
    
    printf("Total: %d\n", count);
    destroyString(&input);
    return 0;
}
