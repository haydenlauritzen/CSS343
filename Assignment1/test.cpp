#include<iostream>
#include<sstream>
#include<string>
#include"poly.h"

using namespace std; 

int main () {

    Poly a;
    Poly b(3);
    Poly c(5, 7);
    Poly d(c); 
    Poly e;
    e = d;
    Poly f(0, 8);
    Poly g(0, 8);

    // Constructor Tests

    std::cout << "Poly A: \nExpected: 0\n";
    std::cout << "Result:   " << a << endl;
    std::cout << "Poly B: \nExpected: 3\n";
    std::cout << "Result:   " << b << endl;
    std::cout << "Poly C: \nExpected: 5x^7\n";
    std::cout << "Result:   " << c << endl;
    std::cout << "Poly D: \nExpected: 5x^7\n";
    std::cout << "Result:   " << d << endl;
    std::cout << "Poly E: \nExpected: 5x^7\n";
    std::cout << "Result:   " << e << endl;

    // Stream Tests

    std::istringstream testStream("1 2 4 5 6 7 -8 0 -1 -1 5 7 -4 3 10 1 -2 0 -1 -1 ");
    cin.rdbuf(testStream.rdbuf());
    cin >> f;
    cin >> g;
    std::cout << "Poly F: \nExpected: 6x^7 + 4x^5 + x^2 - 8\n";
    std::cout << "Result:   " << f << endl;
    std::cout << "Poly G: \nExpected: 5x^7 - 4x^3 + 10x - 2\n";
    std::cout << "Result:   " << g << endl;
    Poly h(0, 3);
    Poly i(0, 4);
    std::istringstream testArith("3 0 2 2 3 1 -1 -1 1 0 1 1 1 2 1 3 -1 -1");
    cin.rdbuf(testArith.rdbuf());
    cin >> h;
    cin >> i;
    std::cout << "Poly H: \nExpected: 2x^2 + 3x + 3\n";
    std::cout << "Result:   " << h << endl;
    std::cout << "Poly I: \nExpected: x^3 + x^2 + x + 1\n";
    std::cout << "Result:   " << i << endl;


    // Equivalence Tests

    cout << "d == c? \nExpected: true\n";
    cout << "Result:   " << ((d == c) ? "true" : "false") << endl;
    cout << "a == c? \nExpected: false\n";
    cout << "Result:   " << ((a == c) ? "true" : "false") << endl;
    cout << "d != c? \nExpected: false\n";
    cout << "Result:   " << ((d != c) ? "true" : "false") << endl;
    cout << "a != c? \nExpected: true\n";
    cout << "Result:   " << ((a != c) ? "true" : "false") << endl; 

    // Arithmetic Tests

    // Poly G 5x^7 - 4x^3 + 10x - 2
    // Poly I x^3 + x^2 + x + 1 
    std::cout << "G + I: \nExpected: 5x^7 - 3x^3 + x^2 + 11x - 1\n";
    std::cout << "Result:   " << (g + i) << endl;
    std::cout << "G - I: \nExpected: 5x^7 - 5x^3 - x^2 - 9x - 3\n";
    std::cout << "Result:   " << (g - i) << endl;   
    std::cout << "G * I: \nExpected: 5x^10 + 5x^9 + 5x^8 + 5x^7 - 4x^6 - 4x^5 + 6x^4 + 4x^3 + 8x^2 + 8x - 2\n";   
    std::cout << "Result:   " << (g * i) << endl;   

    Poly j; // 0
    std::cout << "G + 0: \nExpected: 5x^7 - 4x^3 + 10x - 2 \n";
    std::cout << "Result:   " << (g + j) << endl;
    std::cout << "G - 0: \nExpected: 5x^7 - 4x^3 + 10x - 2 \n";
    std::cout << "Result:   " << (g - j) << endl;   
    std::cout << "G * 0: \nExpected: 0\n";   
    std::cout << "Result:   " << (g * j) << endl;           

    // Assignment Tests

    // Poly H 2x^2 + 3x + 3
    // Poly F 6x^7 + 4x^5 + x^2 - 8
    std::cout << "H += F: \nExpected: 6x^7 + 4x^5 + 3x^2 + 3x - 5\n";
    std::cout << "Result:   " << (h += f) << endl;
    std::cout << "H -= F: \nExpected: 2x^2 + 3x + 3\n";
    std::cout << "Result:   " <<     (h -= f) << endl;   
    std::cout << "H *= F: \nExpected: 12x^9 + 18x^8 + 26x^7 + 12x^6 + 12x^5 + 2x^4 + 3x^3 - 13x^2 - 24x - 24\n";   
    std::cout << "Result:   " << (h *= f) << endl;  
    std::cout << "A = F: \nExpected: 6x^7 + 4x^5 + x^2 - 8\n";   
    std::cout << "Result:   " << (a = f) << endl;  

}