#include "../include/ctools.h"

#define BUF_SIZE 256

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

string f_initString_base(const char* content) {
    string a;
    a.size = strlen(content);
    if (a.size > 0) {
        a.buf = (char*) malloc(strlen(content));
        memcpy(a.buf, &content, strlen(content));
    } else {
        a.buf = NULL;
    }
    return a;
}

string f_initString_var(f_initString_args in) {
    in.content = (in.content)? in.content : "";
    return f_initString_base(in.content);
}

void destroyString(string *a) {
    if (a->buf) {
        free(a->buf);
        a->buf = NULL;
    }
    a->size = 0;
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
    if (size <= 0) {
        size = 4;
    }
    container newStack;
    newStack.size = size;
    newStack.top = -1;
    newStack.buf = (size_t*) malloc(sizeof(size_t) * newStack.size);
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
    a->buf[a->top] = 0;
    a->top--;
    return 1;
}

static void expand_container(container *a) {
    size_t *tmp = malloc(sizeof(size_t) * a->size * 2);
    memcpy(&tmp, a->buf, sizeof(size_t) * a->size);
    memset(&tmp[a->size], 0, sizeof(size_t) * a->size);
    a->size *= 2;
    free(a->buf);
    a->buf = tmp;
}

int push_back(container *a, size_t b) {
    if (a->top ==  a->size - 1) {
        LOG("ERROR: push_back function failed -> out of room\n");
        return 0;
    }
    a->top++;
    if (a->top == a->size) {
        expand_container(a);
    }
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
