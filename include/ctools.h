#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

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