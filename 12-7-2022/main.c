#include "../include/ctools.h"

typedef struct dir {
    string name;
    size_t parent;
    container subDirs;
    unsigned int size;
} Dir;

Dir initDir(const char* name, Dir* parent) {
    Dir newDir;
    newDir.name = initString(name);
    newDir.parent = (size_t) parent;
    newDir.subDirs = initContainer(0);
    newDir.size = 0;
    return newDir;
}

void destroyDir(Dir* dir) {
    destroyString(&dir->name);
    for (int i = 0; i <= dir->subDirs.top; i++) {
        destroyDir((Dir*) dir->subDirs.buf[i]);
    }
    destroyContainer(&(dir->subDirs));
}

FILE* file = NULL;
string input;
Dir root;
Dir* curDir = NULL;

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

Dir* getSubDir(string newDir) {
    for (int i = 0; i <= curDir->subDirs.top; i++) {
        if (!strcmp(newDir.buf, ((Dir*) curDir->subDirs.buf[i])->name.buf)) {
            return (Dir*) curDir->subDirs.buf[i];
        }
    }
    return NULL;
}

void changeDirs(string newDir) {
    if (!strcmp(newDir.buf, "/")) {
        curDir = &root;
    } else if (!strcmp(newDir.buf, "..")) {
        if (curDir->parent) {
            curDir = (Dir*) curDir->parent;
        } else {
            fprintf(stderr, "ERROR: Root directory '%s' has no parent.\n", curDir->name.buf);
        }
    } else {
        Dir* temp = getSubDir(newDir);
        if (temp) {
            curDir = temp;
        } else {
            fprintf(stderr, "ERROR: '%s' has no sub directory '%s'.\n", curDir->name.buf, newDir.buf);
        }
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

        }
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
    unsigned int minDirSize = 0;
    printf("Smallest Directory Size: %d\n", minDirSize);

    destroyDir(&root);
    destroyString(&input);
    fclose(file);
    return 0;
}