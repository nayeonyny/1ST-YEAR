//Inheritance and Polymorphism in C++
#include <iostream>
using namespace std;
//Parent or Base class
class Person{
private:
   string name;
   int age;

public:
    //constructor
    Person(string n, int a) : name(n), age(a){}
    void introduce() {
      cout <<"Hello, I'm "<<name<<", and I'm "<<age<<" years old."<<endl;
    }
    void setValues(string n, int a){
       name = n;
       age = a;
    }
    string getName(){
      return name;
    }
    int getAge(){
      return age;
    }
};
//Child or Derived class
class Student : public Person{
private:
    int idnumber;
public:
    //constructor
    Student(string n, int a, int id) : Person(n,a){
        idnumber = id;
    }
    void introduce() {
     cout<<"Hi! I love programming...\n";
    }
    void displayRecord(){
    cout<<"Name: "<<getName()<<endl;
    cout<<"Age: "<<getAge()<<endl;
    cout<<"Id Number: "<<idnumber<<endl;
    }
    void add(int a, int b, int c){
      cout<<a+b+c<<endl;
    }
    void add(string a, string b, string c){
      cout <<a+b+c<<endl;
    }
    void add(int a, int b, int c, int d, int e){
      cout<<a+b+c+d+e<<endl;
    }
};
int main(){
Person p1("Mel Chor",18);
Student s1("Gas Par",19,111);
p1.introduce();
s1.introduce();
s1.displayRecord();
s1.add(1,2,3);
s1.add("1","2","3");
s1.add(1,2,3,4,5);
return 0;
}
