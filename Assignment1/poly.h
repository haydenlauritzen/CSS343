/**
 * @file poly.h
 * @author Hayden Lauritzen haydenlauritzen@gmail.com
 * @brief Header File for Polynomial
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <cmath> // Math.abs()

/**
 * @brief Stores an array of terms
 * @details Terms are stored as a coefficient and a degree. 
 */
class Poly {

    static const int EMPTY = 0; // denotes no term of that degree

    private:

    /**
     * index - degree of term 
     * value - value of coefficient
     */ 
    int* m_terms;
    // size of polynomial; degree + 1  
    int m_size;     

    public:

    /* Constuctors */

    /**
     * @brief Default Constructor
     * @details Constructs a polynomial of size 1 equal to 0x^0.
     */
    Poly();
    /**
     * @brief Constructs a new Poly object with the largest term
     * @param coeff Value of coefficient.
     * @param degree Value of degree; equal to the index in the array.
     */
    Poly(int, int);
    /**
     * @brief Construct a new Poly object of size one with a coefficient
     * @param coeff Value of coefficient; nx^0 where n is the coefficient.
     */
    Poly(int);
    /**
     * @brief Creates a deep copy
     * @param Poly Polynomial to be copied.
     */
    Poly(const Poly&);
    /**
     * @brief Destroy the Poly object
     * @details Deallocates the dynamically declared array.
     */
    ~Poly();

    /* Arithmetic Operators */

    /**
     * @brief Adds a polynomial
     * @details Adds the lhs and rhs and returns a new Polynomial object.
     * @param p rhs to be added.
     * @return A new polynomial object equal to the two added polynomials.
     */
    Poly operator+(const Poly&) const;
    /**
     * @brief Subtracts a polynomial
     * @details Adds the lhs and rhs and returns a new Polynomial object.
     * @param p rhs to be subtracted.
     * @return A new polynomial object equal to the two added polynomials.
     */
    Poly operator-(const Poly&) const;
    /**
     * @brief Adds a polynomial
     * @details Adds the lhs and rhs and returns a new Polynomial object.
     * @param p rhs to be multiplied.
     * @return A new polynomial object equal to the two added polynomials.
     */
    Poly operator*(const Poly&) const;

    /* Assignment Operators */

    /**
     * @brief Assigns the polynomial and makes a deep copy.
     * @param p rhs to be assigned.
     * @return The reference to the assigned polynomial
     */
    Poly& operator=(const Poly&);
    /**
     * @brief Adds and assigns the polynomial
     * @param p rhs to be added and assigned.
     * @return The reference to the assigned polynomial
     */
    Poly& operator+=(const Poly&);
    /**
     * @brief Subtracts and assigns the polynomial
     * @param rhs to be subtracted and assigned.
     * @return The reference to the assigned polynomial
     */
    Poly& operator-=(const Poly&);
    /**
     * @brief Multiplies and assigns the polynomial
     * @param p rhs to be multiplied and assigned.
     * @return The reference to the assigned polynomial
     */
    Poly& operator*=(const Poly&);

    /* Equivalence Operators */

    /**
     * @brief Checks for polynomial equivalence.
     * @details Polynomials are equivalent if all terms have equal coefficients.
     * @param p rhs to be checked for equivalence.
     * @return true If all terms are equivalent
     * @return false If at least one term is not equivalent.
     */
    bool operator==(const Poly&);
    /**
     * @brief Checks for polynomial equivalence.
     * 
     * @details 
     * Polynomials are inequivalent if any term does not have equal coefficients.
     * Returns the negation of operator==() 
     * 
     * @param p rhs to be checked for inequivelence.
     * @return true If at least one term is not equivalent.
     * @return false If all terms are equivalent
     */
    bool operator!=(const Poly&);

    /* Stream Operators */

    /**
     * @brief Prints the polynomial to the console. 
     *
     * @details 
     * Always uses lowercase x.
     * Nonzero coefficients are always displayed.
     * Zero cofficients are only displayed if the degree is 0.  
     * Coefficient sign is always displayed.
     * One blank space is printed between terms; no other whitespace.
     * > Degree of >1 -> coeff + "x^" + degree.
     * > Degree of 1  -> coeff + "x".
     * > Degree of 0  -> coeff.
     * 
     * @param os std::ostream&
     * @param p Poly object to be printed. 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream&, const Poly&);
    /**
     * @brief Reads in console input to a polynomial.
     * 
     * @details 
     * It is expected that a user enters one coefficient and an exponent repeatedly, 
     * Enters -1 for both when done.
     * 
     * @param is std::istream&
     * @param p Poly object to write into.
     * @return std::istream& 
     */
    friend std::istream& operator>>(std::istream&, Poly&);

    /**
     * @brief Get the coefficient of the term of the degree provided.
     * @param degree degree of term.
     * @return coeffient of term.
     */
    int getCoeff(int) const;
    /**
     * @brief Get the coefficient of the last term
     * @return coeffient of last term.
     */
    int getCoeff() const;
    /**
     * @brief Get the size of the polynomial
     * @details Equivalent to the degree of the polynomial + 1.
     * @return Size of the polynomial.
     */
    int getSize() const;

    /* Mutators */

    /**
     * @brief Set the coefficient of a term
     * @param coeff - Coefficient of term to set.
     * @param degree - Degree of term to set the coefficient of.
     */
    void setCoeff(int, int);

    /* Auxiliary Functions */

    /**
     * @brief Prints the polynomial nicely.
     * 
     * @details 
     * Ignores coefficients of 1
     * Ignores positive signage.    
     */
    void print() const; 

    /**
     * @brief Empties the polynomial
     * @details Deallocates memory and sets the size of the polynomial to 1
     */
    void clear();

};