#include <iostream>
using namespace std;

class fibonacci {
    public :
        void iFibonnacci(int n) {
            if (n <= 0) {
                cout << "n must be greater than 0 " << endl;
                return;
            }
            int a = 0 , b = 1, next;
            cout <<"Fibonnaci In interative: ";
            for (int i = 1; i <=n ;i++) {
                cout << a << " ";
                next = a + b;
                a = b;
                b = next;
            }
            cout << endl;
        }

        int rFibonnacci(int n) {
            if (n <= 1) {
                return n; 
            }
            return rFibonnacci(n-1) + rFibonnacci(n-2);
        }

    void print_recursive(int n) {
        if (n <= 0) {
            cout << "Invalid input. n must be greater than 0." << endl;
            return;
        }
        cout << "Fibonacci In Recursive: ";
        for (int i = 0 ; i < n; ++i) {
        cout << rFibonnacci(i) << " ";
        }
        cout << endl;
    }
};

int main () {
    fibonacci fib;
    int n = 10;

    fib.iFibonnacci(n);
    fib.print_recursive(n);

    return 0;
}