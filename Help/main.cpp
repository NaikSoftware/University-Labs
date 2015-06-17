#include <iostream>

using namespace std;

void sortBubble(int *arr, int size);
void print(int* arr, int size);

int main()
{
    int test[] = {10, 20, -90, 1, 0, 9};
    int size = sizeof(test) / sizeof(int);
    print(test, size);
    sortBubble(test, size);
    print(test, size);
    return 0;
}

void sortBubble(int *arr, int size) {
    for (int n = 0; n < size - 1; n++) {
        for (int m = 0; m <  size - n - 1; m++) {
            if (arr[m + 1] < arr[m])
                swap(arr[m], arr[m + 1]);
        }
    }
}

void print(int* arr, int size) {
    cout << "Array: " << endl;
    for (int n = 0; n < size; n++) {
        cout << arr[n] << ' ';
    }
    cout << endl << endl;
}
