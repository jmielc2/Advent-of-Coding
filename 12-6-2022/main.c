#include "../include/ctools.h"

#define SEQ_LEN 14

int main(int argc, char* argv[]) {
    char* filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
        return -1;
    }

    FILE* file = fopen(filename,  "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open '%s'.\n", filename);
        return -1;
    }

    int letters[26];
    memset(&letters, 0, sizeof(letters));
    int count = 0;
    string input = initString();
    getline(file, &input);
    // printf("%s\n", input.buf);

    unsigned long long int i = 0;
    for (; i < SEQ_LEN; i++) {
        letters[input.buf[i] - 'a']++;
        if (letters[input.buf[i] - 'a'] == 1) {
            count++;
        }
    }

    do {
        if (count == SEQ_LEN) {
            printf("Signal Found At: %lld\n", i);
            break;
        }
        letters[input.buf[i - SEQ_LEN] - 'a']--;
        if (letters[input.buf[i - SEQ_LEN] - 'a'] == 0) {
            count--;
        }
        letters[input.buf[i] - 'a']++;
        if (letters[input.buf[i] - 'a'] == 1) {
            count++;
        }
        i++;
    } while (i < input.size);
    destroyString(input);

    return 0;
}