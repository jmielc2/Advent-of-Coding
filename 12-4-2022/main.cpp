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

    // Do Computation Here

    file.close();
    return 0;
}