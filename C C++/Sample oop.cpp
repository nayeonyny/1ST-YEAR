#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class Myclass {
public:
    void MyFunction() {
        cout << "Skibidi toilet" << endl;
    }
};

class MyGrandChildClass : public Myclass {};

class MyNegChild : private MyGrandChildClass {
private:
    void MyFunction() {
        cout << "AAAAAAAAAAAAAAAAAA" << endl;
    }

public:
    void callMyFunction() {
        MyFunction();
    }
};

int main() {
    MyGrandChildClass myGrandChild;
    myGrandChild.MyFunction(); 

    MyNegChild myNegChild;
    myNegChild.callMyFunction(); 
    return 0;
}