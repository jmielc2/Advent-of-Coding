#include "../include/ctools.h"

const int xOffset[] = {0, 1, 0, -1};
const int yOffset[] = {-1, 0, 1, 0};

int height, width;
container trees;

int isVisible(const int x, const int y) {
    for (int i = 0; i < 4; i++) {
        int tmpX = x;
        int tmpY = y;
        int check = 1;
        while (tmpX > 0 && tmpY > 0 && tmpX < width - 1 && tmpY < height - 1) {
            tmpX += xOffset[i];
            tmpY += yOffset[i];
            container* row1 = (container*) trees.buf[tmpY];
            container* row2 = (container*) trees.buf[y];
            if (row1->buf[tmpX] >= row2->buf[x]) {
                check = 0;
                break;
            }
        }
        if (check) {
            return 1;
        }
    }
    return 0;
}

int getDistance(const int x, const int y, const int dir) {
    int dist = 0;
    int tmpX = x, tmpY = y;
    while (1) {
        tmpX += xOffset[dir];
        tmpY += yOffset[dir];
        if (tmpX < 0 || tmpY < 0 || tmpX >= width || tmpY >= height) {
            break;
        }
        container* row1 = (container*) trees.buf[y];
        container* row2 = (container*) trees.buf[tmpY];
        if (row1->buf[x] <= row2->buf[tmpX]) {
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
    char* filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s | <filename>\n", argv[0]);
        return -1;
    }

    FILE* file = fopen(filename,  "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open '%s'.\n", filename);
        return -1;
    }

    trees = initContainer(99);
    string input = initString("");
    while (!feof(file)) {
        getline(file, &input);
        if (!strcmp("", input.buf)) {
            continue;
        }
        container *tmp = malloc(sizeof(container));
        *tmp = initContainer(99);
        for (int i = 0; i < input.size; i++) {
            push_back(tmp, input.buf[i] - 48);
        }
        push_back(&trees, (size_t) tmp);
    }
    destroyString(&input);
    fclose(file);
    height = trees.top + 1;
    width = ((container*) trees.buf[0])->top + 1;

    int maxScore = 0, count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            count += (isVisible(j, i))? 1 : 0;
            int tmp = calcViewDist(j, i);
            maxScore = (maxScore > tmp)? maxScore : tmp;
        }
    }
    printf("Total Visible Trees: %d\n", count);
    printf("Max Viewing Distance: %d\n", maxScore);

    for (int i = 0; i <= trees.top; i++) {
        destroyContainer((container*) trees.buf[i]);
        free((container*) trees.buf[i]);
    }
    destroyContainer(&trees);
    return 0;
}