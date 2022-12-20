#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

extern int f_getline_var(f_getline_args in);

#define getline(...) f_getline_var((f_getline_args){__VA_ARGS__})

extern string initString();

extern void destroyString(string *a);

extern string substr(const char* buf, int index, int size);

extern container initContainer(int size);

extern void destroyContainer(container *a);

extern int pop_back(container *a);

extern int push_back(container *a, size_t b);

extern void reverse(container *a);