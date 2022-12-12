#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdio.h>

using namespace std;

vector<vector<char>> grid;

void readGrid(ifstream &file) {
    string input;
    bool first = true;
    while (true) {
        getline(file, input);
        if (first) {
            grid = vector<vector<char>>((input.size() + 1) / 4);
            first = false;
        }
        if (input == "") {
            break;
        }
        unsigned long long i = 0;
        while (i < input.size()) {
            if (input[i] != ' ') {
                grid[i / 4].push_back(input[i + 1]);
            }
            i += 4;
        }
    }
    for (auto &a : grid) {
        reverse(a.begin(), a.end());
    }
}

void processMoves(ifstream &file) {
    string input;
    while (!file.eof()) {
        getline(file, input);
        if (input == "") {
            continue;
        }
        int a, b, c;
        stack<char> temp;
        sscanf(input.c_str(), "move %d from %d to %d", &a, &b, &c);
        while (a) {
            temp.push(grid[b - 1].back());
            grid[b - 1].pop_back();
            a--;
        }
        while (!temp.empty()) {
            grid[c - 1].push_back(temp.top());
            temp.pop();
        }
    }
}

int main(int argc, char* argv[]) {
    string filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [<filename>]" << endl;
        return -1;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Failed to open '" << filename << "'." << endl;
        return -1;
    }

    readGrid(file);
    processMoves(file);
    file.close();

    for (auto &a : grid) {
        cout << a.back();
    }
    cout << endl;
    return 0;
}
