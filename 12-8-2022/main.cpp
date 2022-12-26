#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int xOffset[] = {0, 1, 0, -1};
const int yOffset[] = {-1, 0, 1, 0};

int height, width;
vector<vector<int>> trees;

bool isVisible(const int x, const int y) {
    for (int i = 0; i < 4; i++) {
        int tmpX = x;
        int tmpY = y;
        bool check = true;
        while (tmpX > 0 && tmpY > 0 && tmpX < width - 1 && tmpY < height - 1) {
            tmpX += xOffset[i];
            tmpY += yOffset[i];
            if (trees[tmpY][tmpX] >= trees[y][x]) {
                check = false;
                break;
            }
        }
        if (check) {
            return true;
        }
    }
    return false;
}

int getDistance(const int x, const int y, const int dir) {
    int dist = 0;
    int tmpX = x, tmpY = y;
    while (true) {
        tmpX += xOffset[dir];
        tmpY += yOffset[dir];
        if (tmpX < 0 || tmpY < 0 || tmpX >= width || tmpY >= height) {
            break;
        }
        if (trees[y][x] <= trees[tmpY][tmpX]) {
            dist++;
            break;
        }
        dist++;
    }
    return dist;
}

int calcViewDist(const int x, const int y) {
    int score = 1;
    for (int i = 0; i < 4; i++) {
        score *= getDistance(x, y, i);
    }
    return score;
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

    string input;
    while (!file.eof()) {
        getline(file, input);
        if (input == "") {
            continue;
        }

        vector<int> tmp;
        for (char &a : input) {
            tmp.push_back(a - 48);
        }
        trees.push_back(tmp);
    }
    height = (int) trees.size();
    width = (int) trees[0].size();

    int maxScore = 0, count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            count += (isVisible(j, i))? 1 : 0;
            int tmp = calcViewDist(j, i);
            maxScore = (maxScore > tmp)? maxScore : tmp;
        }
    }

    cout << "Total Visible Trees: " << count << endl;
    cout << "Max Viewing Distance: " << maxScore << endl;

    file.close();
    return 0;
}