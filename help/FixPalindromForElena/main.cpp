// C++98

#include <iostream>
#include <strings.h>

using namespace std;

bool isPalindrom(string word, int letterToRemove);

int main() {

    // Read input
    cout << "Input your word, please:" << endl;
    string word;
    getline(cin, word);

    // Calculate
    int index = 0;
    int length = word.length();
    if (length > 1 && length < 100001 && !isPalindrom(word, -1)) {
        for (int i = 0; i < length; i++) {
            if (isPalindrom(word, i)) {
                index = i + 1;
                break;
            }
        }
    }

    // Print result - index of misspelled character
    cout << "Index of error: " << index << endl;

    return 0;
}

bool isPalindrom(string word, int letterToRemove) {
    if (letterToRemove != -1) {
        word.erase(word.begin() + letterToRemove);
    }
    cout << "Check word: " << word << endl;
    int length = word.length();
    for (int i = 0; i < length / 2; i++) {
        if (word[i] != word[length - 1 - i]) {
            return false;
        }
    }
    return true;
}

