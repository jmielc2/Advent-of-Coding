#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define DEBUG 1

#if DEBUG
#define LOG(...) fprintf(stderr, __VA_ARGS__)
#else
#define LOG(...)
#endif

typedef struct {
    char *buf;
    unsigned long long int size;
} string;

typedef struct {
    size_t *buf;
    int top;
    int size;
} container;

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
    while ((a = fgetc(file)) != EOF && a != delim) {
        if (input->size < BUF_SIZE) {
            buf[input->size] = a;
        }
        input->size++;
    }
    input->buf = (char*) malloc(sizeof(char) * (input->size + 1));
    if (!input->buf) {
        perror("malloc failed to allocate space");
        return 0;
    }
    if (input->size >= BUF_SIZE) {
        memcpy(input->buf, buf, BUF_SIZE);
        fseek(file, -1 * (input->size - BUF_SIZE + 1), SEEK_CUR);
        for (int i = BUF_SIZE; i < input->size; i++) {
            a = fgetc(file);
            input->buf[i] = a;
        }
    } else {
        memcpy(input->buf, buf, input->size);
    }
    input->buf[input->size] = '\0';
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
    if (strlen(buf) < index + size) {
        LOG("ERROR: substr function failed -> out of bounds\n");
        return a;
    }
    a.size = size;
    a.buf = (char*) malloc(sizeof(char) * (size + 1));
    memcpy(a.buf, &buf[index], size);
    a.buf[size] = '\0';
    return a;
}

container initContainer(int size) {
    container newStack;
    newStack.size = size;
    newStack.top = -1;
    newStack.buf = (size_t*) malloc(sizeof(size_t) * size);
    return newStack;
}

void destroyContainer(container *a) {
    if (a->buf) {
        free(a->buf);
        a->buf = NULL;
    }
    a->size = 0;
    a->top = -1;
}

int pop_back(container *a) {
    if (a->top < 0) {
        LOG("ERROR: pop_back function failed -> already empty\n");
        return 0;
    }
    a->top--;
    return 1;
}

int push_back(container *a, size_t b) {
    if (a->top ==  a->size - 1) {
        LOG("ERROR: push_back function failed -> out of room\n");
        return 0;
    }
    a->top++;
    a->buf[a->top] = b;
    return 1;
}

void reverse(container *a) {
    size_t *newBuf = (size_t*) malloc(sizeof(size_t) * a->size);
    for (int i = 0; i <= a->top; i++) {
        newBuf[i] = a->buf[a->top - i];
    }
    free(a->buf);
    a->buf = newBuf;
}