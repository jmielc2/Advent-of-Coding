#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

#define SEQ_LEN 14

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

    string input;
    getline(file, input);
    file.close();

    map<char, int> letters;
    unsigned long long int i = 0;
    for (; i < SEQ_LEN; i++) {
        letters[input[i]]++;
    }

    do {
        if (letters.size() == SEQ_LEN) {
            cout << "Signal Found At: " << i << endl;
            break;
        }
        letters[input[i - SEQ_LEN]]--;
        if (letters[input[i - SEQ_LEN]] == 0) {
            letters.erase(input[i - SEQ_LEN]);
        }
        letters[input[i]]++;
        i++;
    } while (i < input.size());

    return 0;
}
