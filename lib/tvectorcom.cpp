#include "tvectorcom.h"

TVectorCom::TVectorCom()
{
    this->tamano = 0;
    this->c = NULL;
}
// Constructor a partir de un tamaño
TVectorCom::TVectorCom(int tamano)
{
    if (tamano < 0)
    {
        this->tamano = 0;
        this->c = NULL;
    }
    else
    {
        this->tamano = tamano;
        this->c = new TComplejo[tamano];
    }
}
// Constructor de copia
TVectorCom::TVectorCom(const TVectorCom &objeto)
{
    this->tamano = objeto.tamano;
    this->c = new TComplejo[this->tamano];
    for (int i = 0; i < this->tamano; i++)
    {
        this->c[i] = objeto.c[i];
    }
}
// Destructor
TVectorCom::~TVectorCom()
{
    this->tamano = 0;

    if (this->c != NULL)
    {
        delete[] this->c;
    }

    this->c = NULL;
}
// Sobrecarga del operador asignación
TVectorCom &TVectorCom::operator=(const TVectorCom &objeto)
{
    if (this != &objeto)
    {
        this->tamano = objeto.tamano;
        delete[] this->c;
        this->c = new TComplejo[this->tamano];
        for (int i = 0; i < this->tamano; i++)
        {
            this->c[i] = objeto.c[i];
        }
    }
    return *this;
}

// MÉTODOS
// Sobrecarga del operador igualdad
bool TVectorCom::operator==(const TVectorCom &object) const
{
    bool igual = true;
    if (this->tamano != object.tamano)
    {
        igual = false;
    }
    else
    {
        for (int i = 0; i < this->tamano; i++)
        {
            if (this->c[i] != object.c[i])
            {
                igual = false;
            }
        }
    }
    return igual;
}
// Sobrecarga del operador desigualdad
bool TVectorCom::operator!=(const TVectorCom &objeto)
{

    return !this->operator==(objeto);
}
// Sobrecarga del operador corchete (parte IZQUIERDA)
TComplejo &TVectorCom::operator[](int pos)
{
    pos--;
    static TComplejo error;
    if (pos >= 0 && pos < this->tamano)
    {
        return this->c[pos];
    }
    else
    {
        error = TComplejo();
        return error;
    }
}

// Sobrecarga del operador corchete (parte DERECHA)
TComplejo TVectorCom::operator[](int pos) const
{
    pos--;
    TComplejo aux;
    if (pos >= 0 && pos < this->tamano)
    {
        aux = this->c[pos];
    }
    else
    {
        aux = TComplejo();
    }
    return aux;
}
// Tamaño del vector (posiciones TOTALES)
int TVectorCom::Tamano() const
{
    return this->tamano;
}
// Cantidad de posiciones OCUPADAS (TComplejo NO VACÍO) en el vector
int TVectorCom::Ocupadas()
{
    int ocupadas = 0;
    for (int i = 0; i < this->tamano; i++)
    {
        if (this->c[i] != TComplejo())
        {
            ocupadas++;
        }
    }
    return ocupadas;
}
// Devuelve TRUE si existe el TComplejo en el vector
bool TVectorCom::ExisteCom(const TComplejo &objeto)
{
    bool existe = false;
    for (int i = 0; i < this->tamano; i++)
    {
        if (this->c[i] == objeto)
        {
            existe = true;
        }
    }
    return existe;
}
// Mostrar por pantalla los TComplejo del vector con PARTE REAL IGUAL O POSTERIOR al argumento
void TVectorCom::MostrarComplejos(double real)
{
    cout << "[";
    for (int i = 0; i < this->tamano; i++)
    {
        if (this->c[i].Re() >= real)
        {
            cout << this->c[i];
            if (i != this->tamano - 1)
            {
                if (this->c[i + 1].Re() >= real)
                    cout << ", ";
            }
        }
    }
    cout << "]";
}
// REDIMENSIONAR el vector de TComplejo
bool TVectorCom::Redimensionar(int tamano)
{
    bool redimensionado = false;
    if (tamano > 0 && tamano != this->tamano)
    {
        TComplejo *aux = new TComplejo[tamano];
        for (int i = 0; i < tamano; i++)
        {
            if (i < this->tamano)
            {
                aux[i] = this->c[i];
            }
            else
            {
                aux[i] = TComplejo();
            }
        }
        delete[] this->c;
        this->c = aux;
        this->tamano = tamano;
        redimensionado = true;
    }
    return redimensionado;
}

// FUNCIONES AMIGAS
// Sobrecarga del operador salida
ostream &operator<<(ostream &os, const TVectorCom &objeto)
{
    os << "[";
    for (int i = 0; i < objeto.tamano; i++)
    {
        os << "(" << i + 1 << ") " << objeto.c[i];
        if (i != objeto.tamano - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
