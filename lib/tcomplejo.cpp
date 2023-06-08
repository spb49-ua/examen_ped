#include "tcomplejo.h"

// El Constructor por defecto , el Constructor a partir de la parte Real  y Constructor a partir de la parte Real  e Imaginaria se podrían AGRUPAR en uno solo, síntesis de los tres, que sería: TComplejo (double = 0, double = 0);

TComplejo::TComplejo(double re, double im)
{
    this->re = re;
    this->im = im;
}

TComplejo::TComplejo(const TComplejo &copia)
{
    this->re = copia.re;
    this->im = copia.im;
}

TComplejo::~TComplejo()
{
    this->re = 0;
    this->im = 0;
}

TComplejo &TComplejo::operator=(const TComplejo &object)
{
    this->re = object.re;
    this->im = object.im;
    return *this;
}

TComplejo TComplejo::operator+(const TComplejo &object)
{
    TComplejo aux;
    aux.re = this->re + object.re;
    aux.im = this->im + object.im;
    return aux;
}

TComplejo TComplejo::operator-(const TComplejo &object)
{
    TComplejo aux;
    aux.re = this->re - object.re;
    aux.im = this->im - object.im;
    return aux;
}

TComplejo TComplejo::operator*(const TComplejo &object)
{
    TComplejo aux;
    aux.re = (this->re * object.re) - (this->im * object.im);
    aux.im = (this->re * object.im) + (this->im * object.re);
    return aux;
}

TComplejo TComplejo::operator+(double num)
{
    TComplejo aux;
    TComplejo aux2(num);
    aux = this->operator+(aux2);
    return aux;
}

TComplejo TComplejo::operator-(double num)
{
    TComplejo aux;
    TComplejo aux2(num);
    aux = this->operator-(aux2);
    return aux;
}

TComplejo TComplejo::operator*(double num)
{
    TComplejo aux;
    TComplejo aux2(num);
    aux = this->operator*(aux2);
    return aux;
}

bool TComplejo::operator==(const TComplejo &object)
{
    if (this->re == object.re && this->im == object.im)
        return true;
    else
        return false;
}

bool TComplejo::operator!=(const TComplejo &object)
{
    if (this->re != object.re || this->im != object.im)
        return true;
    else
        return false;
}

bool TComplejo::operator>(const TComplejo &object){
    if (this->Mod() > object.Mod()){
            return true;
    }
    else if (this->Mod() == object.Mod()){
        if(this->Re() > object.Re()){
            return true;
        }
        else if(this->Re()==object.Re()){
            if (this->Im() > object.Im()){
                return true;
            }
            else 
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool TComplejo::operator<(const TComplejo &object){
    if (this->Mod() < object.Mod()){
            return true;
    }
    else if (this->Mod() == object.Mod()){
        if(this->Re() < object.Re()){
            return true;
        }
        else if(this->Re()==object.Re()){
            if (this->Im() < object.Im()){
                return true;
            }
            else 
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool TComplejo::operator>=(const TComplejo &object){
    if (this->operator>(object) || this->operator==(object)){
        return true;
    }
    else
        return false;
}

bool TComplejo::operator<=(const TComplejo &object){
    if (this->operator<(object) || this->operator==(object)){
        return true;
    }
    else
        return false;
}

double TComplejo::Re() const
{
    return this->re;
}

double TComplejo::Im() const
{
    return this->im;
}

void TComplejo::Re(double re)
{
    this->re = re;
}

void TComplejo::Im(double im)
{
    this->im = im;
}

double TComplejo::Arg() const
{
    double aux;
    aux = atan2(this->im, this->re);
    return aux;
}

double TComplejo::Mod() const
{
    double aux;
    aux = sqrt(pow(this->re, 2) + pow(this->im, 2));
    return aux;
}

ostream &operator<<(ostream &os, const TComplejo &object)
{
    os << "(" << object.re << " " << object.im << ")";
    return os;
}

TComplejo operator+(double num, const TComplejo &object)
{
    TComplejo aux;
    aux.re = object.re + num;
    aux.im = object.im;
    return aux;
}

TComplejo operator-(double num, const TComplejo &object)
{
    TComplejo aux;
    aux.re = num - object.re;
    aux.im = 0 - object.im;
    return aux;
}

TComplejo operator*(double num, const TComplejo &object)
{
    TComplejo aux;
    aux.re = object.re * num;
    aux.im = object.im * num;
    return aux;
}
