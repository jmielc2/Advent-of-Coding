#include "../include/ctools.h"

int DIM_X;
container *grid;

void readGrid(FILE* file) {
    int first = 1;
    string input = initString();
    while (1) {
        getline(file, &input);
        if (first) {
            DIM_X = (input.size + 1) / 4;
            grid = (container*) malloc(sizeof(container) * DIM_X);
            for (int i = 0; i < DIM_X; i++) {
                grid[i] = initContainer(8 * 9);
            }
            first = 0;
        }
        if (!strcmp(input.buf, "")) {
            break;
        }
        int i = 0;
        while (i < input.size) {
            if (input.buf[i] != ' ') {
                push_back(&grid[i / 4], input.buf[i + 1]);
            }
            i += 4;
        }
    }
    for (int i = 0; i < DIM_X; i++) {
        reverse(&grid[i]);
    }
    destroyString(&input);
}

void processMoves(FILE* file) {
    string input = initString();
    destroyString(&input);
    while (!feof(file)) {
        getline(file, &input);
        if (!strcmp(input.buf, "")) {
            continue;
        }
        int a, b, c;
        sscanf(input.buf, "move %d from %d to %d", &a, &b, &c);
        container temp = initContainer(a);
        while (a) {
            push_back(&temp, grid[b - 1].buf[grid[b - 1].top]);
            pop_back(&grid[b - 1]);
            a--;
        }
        while (temp.top >= 0) {
            push_back(&grid[c - 1], temp.buf[temp.top]);
            pop_back(&temp);
        }
        destroyContainer(&temp);
    }
    destroyString(&input);
}

int main(int argc, char* argv[]) {
    char* filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2)  {
        fprintf(stderr, "Usage: %s | <filename>\n", argv[0]);
        return -1;
    }

    FILE* file = fopen(filename,  "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open '%s'.\n", filename);
        return -1;
    }

    readGrid(file);
    processMoves(file);
    fclose(file);
    
    for (int i = 0; i < DIM_X; i++) {
        printf("%c", (char) grid[i].buf[grid[i].top]);
        destroyContainer(&grid[i]);
    }
    printf("\n");
    if (grid) {
        free(grid);
    }
    return 0;
}
