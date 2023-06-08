#ifndef _TCOMPLEJO_H
#define _TCOMPLEJO_H

#include <iostream>
#include <cmath>

using namespace std;

class TComplejo
{

private:
    double re;
    double im;

public:
    // Constructor por defecto : PARTE REAL e IMAGINARIA inicializadas a 0
    TComplejo(double = 0, double = 0);

    // Constructor copia
    TComplejo(const TComplejo &);

    // Destructor
    ~TComplejo();

    // Sobrecarga del operador asignación
    TComplejo &operator=(const TComplejo &a);

    // SOBRECARGA DE OPERADORES ARITMÉTICOS;
    TComplejo operator+(const TComplejo &);
    TComplejo operator-(const TComplejo &);
    TComplejo operator*(const TComplejo &);
    TComplejo operator+(double);
    TComplejo operator-(double);
    TComplejo operator*(double);

    // OTROS OPERADORES
    bool operator==(const TComplejo &); // IGUALDAD de números complejos
    bool operator!=(const TComplejo &); // DESIGUALDAD de números complejos
    bool operator>(const TComplejo &);
    bool operator<(const TComplejo &);
    bool operator>=(const TComplejo &);
    bool operator<=(const TComplejo &);
    double Re() const;                        // Devuelve PARTE REAL
    double Im() const;                        // Devuelve PARTE IMAGINARIA
    void Re(double);                    // Modifica PARTE REAL
    void Im(double);                    // Modifica PARTE IMAGINARIA
    double Arg(void) const;                   // Calcula el Argumento (en Radianes)
    double Mod(void) const;                   // Calcula el Módulo

    // FUNCIONES AMIGAS
    //  Sobrecarga del operador SALIDA
    friend ostream &operator<<(ostream &, const TComplejo &);
    friend TComplejo operator+(double, const TComplejo &);
    friend TComplejo operator-(double, const TComplejo &);
    friend TComplejo operator*(double, const TComplejo &);
};

#endif