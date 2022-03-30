#pragma once

#include <iostream>

class Poly {

    static const int EMPTY = 0; // denotes no term of that degree

    private:

    /* index - degree of term 
     * value - value of coefficient
    */ 
    int* m_terms;  
    int m_size; // size of polynomial; degree + 1    

    public:

    /**
     * @brief Default Constructor
     * Constructs a polynomial of size 1 equal to 0x^0.
     */
    Poly();
    /**
     * @brief Constructs a new Poly object with the largest term
     * @param coeff int - Value of coefficient.
     * @param degree int - Value of degree; equal to the index in the array.
     */
    Poly(int, int);
    /**
     * @brief Construct a new Poly object of size one with a coefficient
     * @param coeff int - Value of coefficient; nx^0 where n is the coefficient.
     */
    Poly(int);
    /**
     * @brief Copy Constructor
     * Creates a deep copy of the polynomial
     * @param Poly - Polynomial to be copied.
     */
    Poly(const Poly&);
    /**
     * @brief Destroy the Poly object
     * Deallocates the dynamically declared array.
     */
    ~Poly();

    Poly operator+(const Poly&) const;
    Poly operator-(const Poly&) const;
    Poly operator*(const Poly&) const;

    Poly& operator=(const Poly&);
    Poly& operator+=(const Poly&);
    Poly& operator-=(const Poly&);
    Poly& operator*=(const Poly&);

    bool operator==(const Poly&);
    bool operator!=(const Poly&);

    friend std::ostream& operator<<(std::ostream&, const Poly&);
    int getCoeff(int) const;
    int getSize() const;

    friend std::istream& operator>>(std::istream&, Poly&);
    void setCoeff(int, int);

    void clear();

};