#include <iostream>
using namespace std;

int smallest(int arr[], int n);

int main() {
    int arr[] = {35, 15, 85, 5, 25, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "The smallest element in the array is: " << smallest(arr, n) << endl;

    return 0;
}

int smallest(int arr[], int n) {
    if (n == 1) {
        return arr[0];
    }
    int smallest1 = smallest(arr, n - 1);
    return (arr[n - 1] < smallest1) ? arr[n - 1] : smallest1;
}