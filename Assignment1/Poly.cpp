#include"Poly.h"

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
    m_terms = new int[p.getSize()];
    for(int i = 0; i < p.getSize(); i++) {
        m_terms[i] = p.getCoeff(i);
    }  
}

Poly::~Poly() 
{
    delete m_terms;
}

Poly Poly::operator+(const Poly&) const
{

}
Poly Poly::operator-(const Poly&) const
{

}
Poly Poly::operator*(const Poly&) const
{

}

Poly& Poly::operator=(const Poly&) 
{
    return *this;
}
Poly& Poly::operator+=(const Poly&)
{
    return *this;
}
Poly& Poly::operator-=(const Poly&)
{
    return *this;
}
Poly& Poly::operator*=(const Poly&)
{
    return *this;
}

bool Poly::operator==(const Poly&)
{
    return 0;
}
bool Poly::operator!=(const Poly&)
{
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Poly& p)
{
    return os;
}
int Poly::getCoeff(int degree) const
{
    if(degree > m_size + 2) throw std::out_of_range("Degree out of Bounds.");
    return this->m_terms[degree+1];
}
int Poly::getSize() const
{
    return this->m_size;
}

std::istream& operator>>(std::istream& is, Poly& p)
{
    return is;
}
void Poly::setCoeff(int, int)
{

}

void Poly::clear() 
{
    delete m_terms;
    m_terms = new int[1]{Poly::EMPTY};
    m_size = 1;

}