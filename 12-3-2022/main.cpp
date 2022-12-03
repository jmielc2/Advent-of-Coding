#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

using namespace std;

int getPriority(const char &a) {
    if (isupper(a)) {
        return a - 'A' + 27;
    }
    return a - 'a' + 1;
}

int main(int argc, char *argv[]) {
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
    
    map<char, int> counts;
    set<char> items, temp;
    int sum = 0;
    string input;

    while (!file.eof()) {
        getline(file, input);
        if (input == "") {
            continue;
        }
        for (char &a : input) {
            items.insert(a);
            counts.emplace(a, 2);
        }

        for (int i = 0; i < 2; i++) {
            temp = items;
            getline(file, input);
            for (char &a : input) {
                if (temp.count(a)) {
                    temp.erase(a);
                    counts[a]--;
                    if (!counts[a]) {
                        sum += getPriority(a);
                        break;
                    }
                }
            }
        }
        items.clear();
        counts.clear();
    }

    cout << "Total: " << sum << endl;
    return 0;
}