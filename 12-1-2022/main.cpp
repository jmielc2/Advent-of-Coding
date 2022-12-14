#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    string filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        cerr << "Usage: " << argv[0] << " | <filename>" << endl;
        return -1;
    }

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Failed to open '" << filename << "'." << endl;
        return -1;
    }

    int max[3];
    int sum = 0;
    string input;

    memset(&max, 0, sizeof(int) * 3);
    while (!infile.eof()) {
        getline(infile, input);
        if (input == "") {
            for (int i = 0; i < 3; i++) {
                if (max[i] > sum) {
                    break;
                } else if (i) {
                    max[i - 1] = max[i];
                }
                max[i] = sum;
            }
            sum = 0;
        } else {
            sum += atoi(input.c_str());
        }
    }
    infile.close();

    cout << "Top Three Elves:" << endl;
    sum = 0;
    for (int i = 0; i < 3; i++) {
        cout << 3 - i << ".) " << max[i] << endl;
        sum += max[i];
    }
    cout << endl <<  "Total: " << sum << endl;
    return 0;
}