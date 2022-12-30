#include "../include/ctools.h"

#define THRESHOLD 100000
#define DESIRED 30000000
#define TOTAL_SPACE 70000000

typedef struct Dir {
    string name;
    size_t parent;
    container subDirs;
    unsigned int size;
} dir;

dir initDir(const char* name, dir* parent) {
    dir newDir;
    newDir.name = initString(name);
    newDir.parent = (size_t) parent;
    newDir.subDirs = initContainer(0);
    newDir.size = 0;
    return newDir;
}

void destroyDir(dir* cur) {
    destroyString(&cur->name);
    for (int i = 0; i <= cur->subDirs.top; i++) {
        destroyDir((dir*) cur->subDirs.buf[i]);
    }
    destroyContainer(&(cur->subDirs));
}

FILE* file = NULL;
string input;
dir root;
dir* curDir = NULL;

container split(const char* cmd, char delim) {
    container res = initContainer(2);
    size_t len = strlen(cmd);
    int i = 0, j, k;
    for (; i < len; i++) {
        while (cmd[i] == delim && i < len) {
            i++;
        }
        j = i;
        while (cmd[i] != delim && i < len) {
            i++;
        }
        k = i;
        if (k - j > 0) {
            string *newPart = malloc(sizeof(string));
            *newPart = substr(cmd, j, k - j);
            push_back(&res, (size_t) newPart);
        }
    }
    return res;
}

dir* getSubDir(string newDir) {
    for (int i = 0; i <= curDir->subDirs.top; i++) {
        if (!strcmp(newDir.buf, ((dir*) curDir->subDirs.buf[i])->name.buf)) {
            return (dir*) curDir->subDirs.buf[i];
        }
    }
    return NULL;
}

void changeDirs(string newDir) {
    if (!strcmp(newDir.buf, "/")) {
        curDir = &root;
    } else if (!strcmp(newDir.buf, "..")) {
        curDir = (dir*) curDir->parent;
    } else {
        dir* temp = getSubDir(newDir);
        curDir = temp;
    }
    getline(file, &input);
    return;
}

void buildDirs() {
    do {
        getline(file, &input);
        if (!strcmp("", input.buf)) {
            continue;
        }
        container parts = split(input.buf, ' ');
        if (!strcmp("dir", ((string*) parts.buf[0])->buf)) {
            dir* newDir = malloc(sizeof(dir));
            *newDir = initDir(((string*) parts.buf[1])->buf, curDir);
            push_back(&curDir->subDirs, (size_t) newDir);
        } else {
            int size = atoi(((string*) parts.buf[0])->buf);
            dir* temp = curDir;
            while (temp) {
                temp->size += size;
                temp = (dir*) temp->parent;
            }
        }
        for (int i = 0; i <= parts.top; i++) {
            destroyString((string*) parts.buf[i]);
            free((string*) parts.buf[i]);
        }
        destroyContainer(&parts);
    } while (input.buf[0] != '$' && !feof(file));
    return;
}

void parseCommand(string cmd) {
    if (!strcmp(cmd.buf, "")) {
        getline(file, &input);
        return;
    }
    container parts = split(cmd.buf, ' ');
    string* instr = (string*) parts.buf[0];
    if (!strcmp(instr->buf, "cd")) {
        changeDirs(*((string*) parts.buf[1]));
    } else {
        buildDirs();
    }

    for (int i = 0; i <= parts.top; i++) {
        destroyString(((string*) parts.buf[i]));
        free((string*) parts.buf[i]);
    }
    destroyContainer(&parts);
}

unsigned int isValidSize(dir *node,  int *count) {
    unsigned int sum = 0;
    if (node->size <= THRESHOLD) {
        (*count)++;
        sum += node->size;
    }
    for (int i = 0; i <= node->subDirs.top; i++) {
        sum += isValidSize((dir*) node->subDirs.buf[i], count);
    }
    return sum;
}

unsigned int smallestDir(dir* node) {
    int revised = root.size - node->size;
    if (TOTAL_SPACE - revised >= DESIRED) {
        unsigned int min = node->size;
        for (int i = 0; i <= node->subDirs.top; i++) {
            unsigned int temp = smallestDir((dir*) node->subDirs.buf[i]);
            min = (temp < min)? temp : min;
        }
        return min;
    }
    return INT_MAX;
}

int main(int argc, char* argv[]) {
    char* filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
        return -1;
    }

    file = fopen(filename,  "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open '%s'.\n", filename);
        return -1;
    }

    root = initDir("/", NULL);
    curDir = &root;
    getline(file, &input);
    while (!feof(file)) {
        string temp = substr(input.buf, 2, input.size - 2);
        parseCommand(temp);
        destroyString(&temp);
    }
    unsigned int minDirSize = smallestDir(&root);
    int count = 0;
    unsigned int space = isValidSize(&root, &count);
    printf("Number of Valid Directories: %d (%d bytes)\n", count, space);
    printf("Optimal Directory Size: %d\n", minDirSize);

    destroyDir(&root);
    destroyString(&input);
    fclose(file);
    return 0;
}