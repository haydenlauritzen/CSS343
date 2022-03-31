#include "poly.h"

Poly::Poly() : m_size(1)
{
    m_terms = new int[m_size]{Poly::EMPTY};
}

Poly::Poly(int coeff, int degree) : m_size(degree+1)
{
    m_terms = new int[m_size]{Poly::EMPTY};
    m_terms[degree] = coeff;
}

Poly::Poly(int coeff) : m_size(1)
{
    m_terms = new int[m_size]{coeff};
}

Poly::Poly(const Poly& p) : m_size(p.getSize())
{
    m_terms = new int[m_size]{Poly::EMPTY};
    for(int i = 0; i < m_size; i++) {
        m_terms[i] = p.getCoeff(i);
    }
}

Poly::~Poly() 
{
    delete[] m_terms;
    m_terms = nullptr;
}

Poly Poly::operator+(const Poly& p) const
{
    // Finds degree of final sum, which is the largest degree
    int finalSize = (this->getSize() > p.getSize()) ? this->getSize() : p.getSize();
    /* 
     * Finds greatest common term between polynomials; 
     * no arithmetic needs to occur after this term
     * and helps avoid out-of-bounds memory access.
    */
    int greatestCommonTerm = this->getSize() < p.getSize() ? this->getSize()-1 : p.getSize()-1;
    Poly newPoly(this->getCoeff(), finalSize-1);
    // Iterates through the polynomial and adds the coefficients of each term.
    for(int i = 0; i < greatestCommonTerm; ++i)
    {
        newPoly.setCoeff(this->getCoeff(i) + p.getCoeff(i), i);
    }
    // Copy rest of lhs as rhs is 0
    if(this->getSize() > p.getSize()) 
    {
        for(int i = greatestCommonTerm; i < this->getSize(); ++i) 
        {
            newPoly.setCoeff(this->getCoeff(i), i);
        }
    }
    // Copy rest of rhs as lhs is 0.
    else if(this->getSize() < p.getSize())
    {
        for(int i = greatestCommonTerm; i < p.getSize(); ++i) 
        {
            newPoly.setCoeff(p.getCoeff(i), i);
        }
    }
    return newPoly;
}
Poly Poly::operator-(const Poly& p) const
{
    // Finds degree of final sum, which is the largest degree
    int finalSize = (this->getSize() > p.getSize()) ? this->getSize() : p.getSize();
    /* 
     * Finds greatest common term between polynomials; 
     * no arithmetic needs to occur after this term
     * and helps avoid out-of-bounds memory access.
    */
    int greatestCommonTerm = this->getSize() < p.getSize() ? this->getSize()-1 : p.getSize()-1;
    Poly newPoly(this->getCoeff(), finalSize-1);
    // Iterates through the polynomial and adds the coefficients of each term.
    for(int i = 0; i < greatestCommonTerm; ++i)
    {
        newPoly.setCoeff(this->getCoeff(i) - p.getCoeff(i), i);
    }
    // Copy rest of lhs as rhs is 0
    if(this->getSize() > p.getSize()) 
    {
        for(int i = greatestCommonTerm; i < this->getSize(); ++i) 
        {
            newPoly.setCoeff(this->getCoeff(i), i);
        }
    }
    // Copy rest of rhs as lhs is 0.
    else if(this->getSize() < p.getSize())
    {
        for(int i = greatestCommonTerm; i < p.getSize(); ++i) 
        {
            newPoly.setCoeff(p.getCoeff(i), i);
        }
    }
    return newPoly;
}Poly Poly::operator*(const Poly& p) const
{
    // Iterates through the polynomial and multiplies the coefficients of each term.
    Poly newPoly(Poly::EMPTY, this->getSize() + p.getSize() - 1); 
    // equivalent to (size - 1) + (size - 1) +1
    // Begin FOIL of polynomials
    for(int i = 0; i < this->getSize(); ++i)
    {
        if(this->getCoeff(i) == 0) continue;
        for(int j = 0; j < p.getSize(); ++j)
        {
            if(p.getCoeff(j) == 0) continue;
            newPoly.setCoeff(newPoly.getCoeff(i+j) + (this->getCoeff(i) * p.getCoeff(j)), i+j);
        }
    }
    return newPoly;
}

Poly& Poly::operator=(const Poly& p) 
{
    // deallocate memory
    delete[] m_terms;
    m_terms = nullptr;
    m_size = p.getSize();
    m_terms = new int[this->getSize()];
    for(int i = 0; i < this->getSize(); i++) {
        m_terms[i] = p.getCoeff(i);
    }
    return *this; 
}
Poly& Poly::operator+=(const Poly& p)
{
    // Calls addition operator overload and assignment overload.
    return this->operator=(this->operator+(p));
}
Poly& Poly::operator-=(const Poly& p)
{
    // Calls subtract operator overload and assignment overload.
    return this->operator=(this->operator-(p));
}
Poly& Poly::operator*=(const Poly& p)
{
    // Calls addition operator overload and assignment overload.
    return this->operator=(this->operator*(p));
}

bool Poly::operator==(const Poly& p)
{
    /* Iterates through every term of the polynomial and checks the
     * equvalence of every coefficient of term and returns 0 if false
     * otherwise returns true.
     */
    if(this->getSize() != p.getSize()) return 0;
    for(int i = 0; i < this->getSize(); ++i)
    {
        if(this->getCoeff(i) != p.getCoeff(i)) return 0;
    }
    return 1;
}
bool Poly::operator!=(const Poly& p)
{
    // Returns the negation of operator==()
    return !(this->operator==(p));
}

std::ostream& operator<<(std::ostream& os, const Poly& p)
{
    // Counts number of terms in polynomial for delimiters.
    int numTerms = 0;
    for(int i = 0; i < p.getSize(); ++i)  
    {
        if(p.m_terms[i] != 0) ++numTerms;
    }
    // If the polynomial is equal to 0, print 0 and return.
    if(numTerms == 0) 
    {
        std::cout << "0";
        return os;
    }
    // Iterate backwards through the polynomial
    bool firstTerm = true;
    for(int degree = p.getSize()-1; degree >= 0; --degree) 
    {
        int coeff;
        if(firstTerm)
        {
            coeff = p.getCoeff(degree);
        }
        // If the term is not the first term, remove the sign for formatting.
        else
        {
            coeff = std::abs(p.getCoeff(degree));
        }
        // If coefficient is 0, skip to the next term
        if(coeff == 0) continue;
        if(numTerms >= 1 && !firstTerm)
        {
            if(p.getCoeff(degree) >= 0) 
            {
                std::cout << " + ";  
            }
            else
            {
                std::cout << " - ";  
            }
            --numTerms;
        }
        switch(degree)
        {
        case 0:
            std::cout << coeff;
            break;
        case 1:
            if(coeff == 1) 
            {
                std::cout << "x";
            }
            else 
            {
                std::cout << coeff << "x";
            }
            break;
        default:
            if(coeff == 1)
            {
                std::cout << "x^" << degree;
            }
            else 
            {
            std::cout << coeff << "x^" << degree;
            }
            break;
        }
        if(firstTerm) firstTerm = false;
    }
    return os;
}
int Poly::getCoeff(int degree) const
{
    if(degree > m_size + 1) throw std::out_of_range("Degree out of Bounds.");
    return this->m_terms[degree];
}
int Poly::getCoeff() const
{
    return this->m_terms[this->getSize()-1];
}
int Poly::getSize() const
{
    return this->m_size;
}

std::istream& operator>>(std::istream& is, Poly& p)
{
    int coeff, degree;
    while(!std::cin.eof())
    {
        std::cin >> coeff >> degree;
        if(degree == -1 && coeff == -1) break;
        if(degree > p.getSize() + 1)
        {
            //TODO increase
        }
        p.setCoeff(coeff, degree);

    } 
    return is;
}
void Poly::setCoeff(int coeff, int degree)
{
    if(degree > this->getSize() + 1)
    {
        // Will have to resize Poly
    }
    else
    {
        m_terms[degree] = coeff;    
    }
}

void Poly::clear() 
{
    delete[] m_terms;
    m_terms = new int[1]{Poly::EMPTY};
    m_size = 1;

}