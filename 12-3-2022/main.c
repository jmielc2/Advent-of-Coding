#include "../include/ctools.h"
#include <ctype.h>

int getPriority(const char a) {
    if (isupper(a)) {
        return a - 'A' + 27;
    }
    return a - 'a' + 1;
}

int main(int argc, char* argv[]) {
    char* filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
        return -1;
    }

    FILE* file = fopen(filename,  "r");
    if (!file) {
        fprintf(stderr, "Failed to open '%s'.\n", filename);
        return -1;
    }

    int sum = 0;
    string input = initString();
    char items[26 * 2], temp[26 * 2], counts[26 * 2];
    while (!feof(file)) {
        if (!getline(file, &input)) {
            fprintf(stderr, "Error: getline function failed.\n");
            return -1;
        }
        if (!strcmp("", input.buf)) {
            continue;
        }
        memset(&items, 0, sizeof(items));
        memset(&counts, 0, sizeof(counts));
        for (int i = 0; i < input.size; i++) {
            int index = getPriority(input.buf[i]) - 1;
            items[index] = 1;
            counts[index] = 2;
        }
        for (int i = 0; i < 2; i++) {
            memcpy(&temp, &items, sizeof(items));
            if (!getline(file, &input)) {
                fprintf(stderr, "Error: getline function failed.\n");
                return -1;
            }
            for (int j = 0; j < input.size; j++) {
                int index = getPriority(input.buf[j]) - 1;
                if (temp[index]) {
                    counts[index]--;
                    temp[index] = 0;
                    if (!counts[index]) {
                        sum += getPriority(input.buf[j]);
                        break;
                    }
                }
            }
        }
    }

    printf("Total: %d\n", sum);
    destroyString(input);
    return 0;
}