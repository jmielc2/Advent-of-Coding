#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 16

typedef struct {
    char *buf;
    int size;
} string;

typedef struct {
    FILE* file;
    string* input;
    char delim;
} f_getline_args;

int f_getline_base(FILE* file, string *input, char delim) {
    if (input->buf != NULL) {
        free(input->buf);
    }
    input->size = 0;
    char buf[BUF_SIZE], a;
    int size = 0;
    while ((a = fgetc(file)) != EOF && a != delim) {
        if (size == BUF_SIZE) {
            fprintf(stderr, "BUF_SIZE is too small.\n");
            return 0;
        }
        buf[size] = a;
        size++;
    }
    input->buf = malloc(sizeof(char) * (size + 1));
    if (!input->buf) {
        perror("malloc failed to allocate space.");
        return 0;
    }
    memcpy(input->buf, buf, size);
    input->buf[size] = '\0';
    input->size = size;
    return 1;
}

int f_getline_var(f_getline_args in) {
    char delim = (in.delim)? in.delim : '\n';
    return f_getline_base(in.file, in.input, delim);
}

#define getline(...) f_getline_var((f_getline_args){__VA_ARGS__})

string initString() {
    string a;
    a.buf = NULL;
    a.size = 0;
    return a;
}

void destroyString(string a) {
    if (a.buf) {
        free(a.buf);
    }
}

string substr(const char* buf, int index, int size) {
    string a = initString();
    a.size = size;
    a.buf = malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < size; i++) {
        a.buf[i] = buf[index + i]; 
    }
    a.buf[size] = '\0';
    return a;
}

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
        fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
        return -1;
    }

    FILE* file = fopen(filename,  "r");
    if (!file) {
        fprintf(stderr, "Failed to open '%s'.\n", filename);
        return -1;
    }

    int count = 0;
    string input = initString();
    while (!feof(file)) {
        if (getline(file, &input)) {
            if (!strcmp("", input.buf)) {
                continue;
            }
            int i = 0, j = 0;
            int vals[4];
            for (int k = 0; k < 4; k++) {
                while (j < input.size && input.buf[j] >= 48 && input.buf[j] <= 57) {
                    j++;
                }
                string a = substr(input.buf, i, j - i);
                vals[k] = atoi(a.buf);
                j++;
                i = j;
                destroyString(a);
            }
            if (overlap(vals)) {
                count++;
            }
        }
    }

    printf("Total: %d\n", count);
    destroyString(input);
    return 0;
}