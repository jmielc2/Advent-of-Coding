#include "../include/ctools.h"

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
        
        // Do Processing Here

    }
    fclose(file);
    
    printf("Total: %d\n", count);
    destroyString(input);
    return 0;
}