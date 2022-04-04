#pragma once

#include <iostream>
#include <cmath>

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

    /**
     * @brief Adds a polynomial
     * Adds the lhs and rhs and returns a new Polynomial object.
     * @param p - rhs to be added.
     * @return Poly - A new polynomial object equal to the two added polynomials.
     */
    Poly operator+(const Poly&) const;
    /**
     * @brief Subtracts a polynomial
     * Adds the lhs and rhs and returns a new Polynomial object.
     * @param p - rhs to be subtracted.
     * @return Poly - A new polynomial object equal to the two added polynomials.
     */
    Poly operator-(const Poly&) const;
    /**
     * @brief Adds a polynomial
     * Adds the lhs and rhs and returns a new Polynomial object.
     * @param p - rhs to be multiplied.
     * @return Poly - A new polynomial object equal to the two added polynomials.
     */
    Poly operator*(const Poly&) const;

    /**
     * @brief Assigns the polynomial
     * Creates a deep copy of the polynomial
     * @param p - rhs to be assigned.
     * @return Poly& - The reference to the assigned polynomial
     */
    Poly& operator=(const Poly&);
    /**
     * @brief Adds and assigns the polynomial
     * Adds the polynomial and assigns the result.
     * @param p - rhs to be added and assigned.
     * @return Poly& - The reference to the assigned polynomial
     */
    Poly& operator+=(const Poly&);
    /**
     * @brief Subtracts and assigns the polynomial
     * Adds the polynomial and assigns the result.
     * @param p - rhs to be subtracted and assigned.
     * @return Poly& - The reference to the assigned polynomial
     */
    Poly& operator-=(const Poly&);
    /**
     * @brief Multiplies and assigns the polynomial
     * Multiplies the polynomial and assigns the result.
     * @param p - rhs to be multiplied and assigned.
     * @return Poly& - The reference to the assigned polynomial
     */
    Poly& operator*=(const Poly&);

    /**
     * @brief Polynomial equivelence.
     * TODO
     * @param p - rhs to be checked for equivelence.
     * @return true TODO
     * @return false TODO
     */
    bool operator==(const Poly&);
    /**
     * @brief Polynomial inequivelence.
     * TODO
     * @param p - rhs to be checked for inequivelence.
     * @return true TODO
     * @return false TODO
     */
    bool operator!=(const Poly&);

    /**
     * @brief Ostream overload
     * TODO
     * @param os std::ostream&
     * @param p const Poly& - Poly object to be printed. 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream&, const Poly&);
    /**
     * @brief Prints the polynomial nicely.
     * Ignores coefficients of 1
     * Ignores positive signage.    
     */
    void print();

    /**
     * @brief Get the coefficient of a term
     * Returns the coefficient of the term with the degree provided.
     * @param degree int - degree of term.
     * @return int - coeffient of term.
     */
    int getCoeff(int) const;
    /**
     * @brief Get the coefficient of the last term
     * @return int - coeffient of last term.
     */
    int getCoeff() const;
    /**
     * @brief Get the size of the polynomial
     * Equivalent to the degree of the polynomial + 1.
     * @return int - Size of the polynomial.
     */
    int getSize() const;

    /**
     * @brief TODO
     * 
     * @return std::istream& 
     */
    friend std::istream& operator>>(std::istream&, Poly&);
    /**
     * @brief Set the coefficient of a term
     * @param coeff - Coefficient of term to set.
     * @param degree - Degree of term to set the coefficient of.
     */
    void setCoeff(int, int);

    /**
     * @brief Empties the polynomial
     * Deallocates memory and sets the size of the polynomial to 1
     */
    void clear();

};