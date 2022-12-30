#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define THRESHOLD 100000
#define DESIRED 30000000
#define TOTAL_SPACE 70000000

struct dir {
    string name;
    dir* parent;
    vector<dir> subDirs;
    map<string, unsigned int> files;
    unsigned int size;

    dir(string name, dir* parent) {
        this->name = name;
        this->parent = parent;
        this->size = 0;
    }
};

ifstream file;
string input;
dir root("/", nullptr);
dir* curDir = nullptr;

vector<string> split(const string &cmd, const char delim) {
    vector<string> res;
    for (unsigned long long int i = 0; i < cmd.size(); i++) {
        if (res.size() == 0 || (cmd[i] == delim && res.back() != "")) {
            res.push_back("");
        }
        if (cmd[i] == delim) {
            continue;
        }
        res.back().push_back(cmd[i]);
    }
    return res;
}

dir* getSubDir(const string &newDir) {
    for (auto &subDir : curDir->subDirs) {
        if (subDir.name == newDir) {
            return &subDir;
        }
    }
    return nullptr;
}

void changeDirs(const string &newDir) {
    if (newDir == "/") {
        curDir = &root;
    } else if (newDir == "..") {
        if (curDir->parent) {
            curDir = curDir->parent;
        } else {
            cerr << "ERROR: Root directory " << curDir->name << " has no parent." << endl;
        }
    } else {
        dir* temp = getSubDir(newDir);
        if (temp) {
            curDir = temp;
        } else {
            cerr << "ERROR: " << curDir->name << " has no sub directory '" << newDir << "'." << endl;
        }
    }
    getline(file, input);
}

void buildDirs() {
    do {
        getline(file, input);
        if (input == "") {
            continue;
        }
        vector<string> parts = split(input, ' ');
        if (parts[0] == "dir") {
            if (!getSubDir(parts[1])) {
                curDir->subDirs.push_back(dir(parts[1], curDir));
            }
        } else {
            if (!curDir->files.count(parts[1])) {
                int size = atoi(parts[0].c_str());
                curDir->files.emplace(parts[1], size);
                dir* temp = curDir;
                while (temp) {
                    temp->size += size;
                    temp = temp->parent;
                }
            }
        }
    } while (input[0] != '$' && !file.eof());
}

void parseCommand(string cmd) {
    if (cmd == "") {
        getline(file, input);
        return;
    }
    vector<string> parts = split(cmd, ' ');
    if (parts[0] == "cd") {
        changeDirs(parts[1]);
    } else if (parts[0] == "ls") {
        buildDirs();
    }
}

unsigned int isValidSize(dir &node, int &count) {
    unsigned int sum = 0;
    if (node.size <= THRESHOLD) {
        count++;
        sum += node.size;
    }
    for (auto &subDir : node.subDirs) {
        sum += isValidSize(subDir, count);
    }
    return sum;
}

unsigned int smallestDir(dir &node) {
    int revised = root.size - node.size;
    if (TOTAL_SPACE - revised >= DESIRED) {
        unsigned int min = node.size;
        for (auto &subDir : node.subDirs) {
            unsigned int temp = smallestDir(subDir);
            if (min > temp) {
                min = temp;
            }
        }
        return min;
    }
    return INT_MAX;
}

int main(int argc, char* argv[]) {
    string filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        cerr << "Usage: " << argv[0] << " | <filename>" << endl;
        return -1;
    }

    file.open(filename);
    if (!file.is_open()) {
        cerr << "Error: Failed to open '" << filename << "'." << endl;
        return -1;
    }

    curDir = &root;
    getline(file, input);
    while (!file.eof()) {
        parseCommand(input.substr(2, input.size() - 2));
    }

    unsigned int minDirSize = smallestDir(root);
    int count = 0;
    unsigned int space = isValidSize(root, count);
    cout << "Number of Valid Directories: " << count << " (" << space << " bytes)" << endl;
    cout << "Optimal Directory Size: " << minDirSize << endl;

    file.close();
    return 0;
}