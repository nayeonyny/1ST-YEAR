#include <iostream>
using namespace std;
#define MAX 7
int Twosum ();
int Twosum () {
    int i,j;
    int array[] = {1,2,3,4,5,6};
    int Target = 7;
    int arraySize = sizeof(array)/ sizeof(array[0]);

    for (i=0; i<arraySize; i++ ) {
        for (j=i+1; j<arraySize; j++ ) {
                if (array[i] + array[j] == Target) {
                    cout << setw(1) << array[i] << " + " << setw(1) << array[j] << " is " << setw(1) << Target << endl;
                }
        }
    }
    return 0;
}
int main () {
    Twosum();
}