#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

    int count = 0;
    string input;
    while (!file.eof()) {
        getline(file, input);
        if (input == "") {
            continue;
        }
        
        // Processing Input Here

    }
    file.close();

    cout << "Total: " << count << endl;
    return 0;
}
