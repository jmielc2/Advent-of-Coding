#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define WIN 6
#define DRAW 3

enum {X=0,Y=3,Z=6};
enum {A=1,B=2,C=3};

int getPlay(const int &opp, const int &outcome) {
    int play;
    if (outcome == Z) {
        if (opp == C) {
            play = A;
        } else {
            play = opp + 1;
        }
    } else if (outcome == X) {
        if (opp == A) {
            play = C;
        } else {
            play = opp - 1;
        }
    } else {
        play = opp;
    }
    return play + outcome;
}

int main() {
    string filename = "input.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Failed to open " << filename << "." << endl;
        return -1;
    }

    int round, score = 0;
    string input;
    while (!file.eof()) {
        round = 0;
        getline(file, input);
        if (input == "") {
            continue;
        }
        int opp = input[0] - 'A' + 1;
        switch (input[2]) {
        case('X'):
            round += getPlay(opp, X);
            break;
        case('Y'):
            round += getPlay(opp, Y);
            break;
        case('Z'):
            round += getPlay(opp, Z);
            break;
        }
        // cout << input << " -> " << round << endl;
        score += round;
    }

    cout << "Final Score: " << score << endl;
    return 0;
}