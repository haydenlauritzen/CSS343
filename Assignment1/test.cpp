#include<iostream>
#include"Poly.h"

using namespace std; 

int main () {

    Poly a;
    Poly b(3);
    Poly c(5, 7);
    Poly d(c);

    cout << "Poly A: \n Expected: 0\n";
    cout << a << endl;
    cout << "Poly B: \n Expected: 3\n";
    cout << b << endl;
    cout << "Poly A: \n Expected: 5x^7\n";
    cout << c << endl;
    cout << "Poly A: \n Expected: 5x^7\n";
    cout << d << endl;

    int pause; 
    cin >> pause;
}