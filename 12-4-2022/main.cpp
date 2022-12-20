#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool contains(int vals[]) {
    return (vals[0] <= vals[2] && vals[1] >= vals[3]) || (vals[0] >= vals[2] && vals[1] <= vals[3]);
}

bool overlap(int vals[]) {
    return (vals[0] >= vals[2] && vals[0] <= vals[3]) || (vals[1] >= vals[2] && vals[1] <= vals[3]) || contains(vals);
}

int main(int argc, char* argv[]) {
    string filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        cerr << "Usage: " << argv[0] << " | <filename>" << endl;
        return -1;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Failed to open '" << filename << "'." << endl;
        return -1;
    }

    int count = 0;
    string input;
    while (!file.eof()) {
        getline(file, input);
        if (input == "") {
            continue;
        }
        unsigned long long i = 0, j = 0, k = 0;
        int vals[4];
        while (k < 4) {
            while (j < input.size() && isdigit(input[j])) {
                j++;
            }
            vals[k] = atoi(input.substr(i, j - i).c_str());
            j++;
            i = j;
            k++;
        }
        if (overlap(vals)) {
            count++;
        }
    }
    file.close();

    cout << "Total: " << count << endl;
    return 0;
}