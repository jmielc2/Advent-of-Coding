#include "../include/ctools.h"

typedef struct file {
    string name;
    unsigned int size;
};

typedef struct dir {
    string name;
    struct dir* parent;
    container subDirs;
    container files;
    unsigned int size;
};

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

    fclose(file);
    return 0;
}