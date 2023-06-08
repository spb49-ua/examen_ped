#include "tlistacom.h"
using namespace std;

TListaNodo::TListaNodo()
{
    this->anterior = NULL;
    this->siguiente = NULL;
    this->e = TComplejo();
}

TListaNodo::TListaNodo(const TListaNodo &objeto)
{
    this->e = objeto.e;
    this->anterior = objeto.anterior;
    this->siguiente = objeto.siguiente;
}

TListaNodo::~TListaNodo()
{
    this->e.~TComplejo();
    this->anterior = NULL;
    this->siguiente = NULL;
}

TListaNodo &TListaNodo::operator=(const TListaNodo &objeto)
{
    if (this != &objeto)
    {
        (*this).~TListaNodo();
        this->e = objeto.e;
        this->anterior = objeto.anterior;
        this->siguiente = objeto.siguiente;
    }
    return *this;
}

TListaPos::TListaPos()
{
    this->pos = NULL;
}

TListaPos::TListaPos(const TListaPos &objeto)
{
    this->pos = objeto.pos;
}

TListaPos::~TListaPos()
{
    this->pos = NULL;
}

TListaPos &TListaPos::operator=(const TListaPos &objeto)
{
    if (this != &objeto)
    {
        this->pos = objeto.pos;
    }
    return *this;
}

bool TListaPos::operator==(const TListaPos &objeto) const
{
    return this->pos == objeto.pos;
}

bool TListaPos::operator!=(const TListaPos &objeto) const
{
    return this->pos != objeto.pos;
}

TListaPos TListaPos::Anterior() const
{
    TListaPos aux;
    if (this->pos != NULL && this->pos->anterior != NULL)
    {
        aux.pos = this->pos->anterior;
    }
    return aux;
}

TListaPos TListaPos::Siguiente() const
{
    TListaPos aux;
    if (this->pos != NULL && this->pos->siguiente != NULL)
    {
        aux.pos = this->pos->siguiente;
    }
    return aux;
}

bool TListaPos::EsVacia() const
{
    return this->pos == NULL;
}

TListaCom::TListaCom()
{
    this->primero = NULL;
    this->ultimo = NULL;
}

TListaCom::TListaCom(const TListaCom &object)
{
    this->primero = NULL;
    this->ultimo = NULL;
    TListaNodo *aux;
    aux = object.ultimo;
    while (aux != NULL)
    {
        this->InsCabeza(aux->e);
        aux = aux->anterior;
    }
}

TListaCom::~TListaCom()
{
    TListaNodo *aux;

    while (this->primero)
    {

        aux = this->primero;
        this->primero = this->primero->siguiente;
        delete aux;
    }

    this->ultimo = NULL;
}

TListaCom &TListaCom::operator=(const TListaCom &object)
{
    if (this != &object)
    {
        (*this).~TListaCom();
        TListaNodo *aux;
        aux = object.ultimo;
        while (aux != NULL)
        {
            this->InsCabeza(aux->e);
            aux = aux->anterior;
        }
    }
    return *this;
}

bool TListaCom::operator==(const TListaCom &object) const
{
    TListaNodo *aux1, *aux2;
    bool iguales = true;
    aux1 = this->primero;
    aux2 = object.primero;
    while (aux1 != NULL && aux2 != NULL && iguales)
    {
        if (aux1->e != aux2->e)
        {
            iguales = false;
        }
        aux1 = aux1->siguiente;
        aux2 = aux2->siguiente;
    }
    if (aux1 != NULL || aux2 != NULL)
    {
        iguales = false;
    }
    return iguales;
}

bool TListaCom::operator!=(const TListaCom &object) const
{
    return !(*this == object);
}

TListaCom TListaCom::operator+(const TListaCom &object) const
{
    TListaCom aux(object);
    TListaCom aux2;
    aux2 = *this;
    TListaNodo *aux3;
    aux3 = aux2.ultimo;
    while (aux3 != NULL)
    {
        aux.InsCabeza(aux3->e);
        aux3 = aux3->anterior;
    }
    return aux;
}

/*TListaCom TListaCom::operator- (const TListaCom& object) const {
    TListaCom aux(*this);
    TListaNodo *aux2;
    aux2=object.primero;
    while(aux2!=NULL){
        aux.Borrar(aux2->e);
        aux2=aux2->siguiente;
    }
    return aux;
}*/

// Sobrecarga del operador resta
TListaCom TListaCom::operator-(const TListaCom &lista) const
{
    TListaCom aux(*this);
    TListaNodo *aux2;
    aux2 = lista.primero;
    while (aux2 != NULL)
    {
        aux.BorrarTodos(aux2->e);
        aux2 = aux2->siguiente;
    }
    return aux;
}

bool TListaCom::EsVacia() const
{
    return this->primero == NULL;
}

bool TListaCom::InsCabeza(const TComplejo &object)
{
    TListaNodo *aux;
    aux = new TListaNodo;
    if (aux != NULL)
    {
        aux->e = object;
        aux->siguiente = this->primero;
        aux->anterior = NULL;
        if (this->primero != NULL)
        {
            this->primero->anterior = aux;
        }
        this->primero = aux;
        if (this->ultimo == NULL)
        {
            this->ultimo = aux;
        }
        return true;
    }
    return false;
}

bool TListaCom::InsertarI(const TComplejo &object, const TListaPos &pos)
{
    if (pos.pos == NULL)
    {
        return false;
    }
    TListaNodo *aux;
    aux = new TListaNodo;
    if (aux != NULL)
    {
        aux->e = object;
        aux->siguiente = pos.pos;
        aux->anterior = pos.pos->anterior;
        if (pos.pos->anterior != NULL)
        {
            pos.pos->anterior->siguiente = aux;
        }
        pos.pos->anterior = aux;
        if (pos.pos == this->primero)
        {
            this->primero = aux;
        }
        return true;
    }
    return false;
}

bool TListaCom::InsertarD(const TComplejo &object, const TListaPos &pos)
{
    if (pos.pos == NULL)
    {
        return false;
    }
    TListaNodo *aux;
    aux = new TListaNodo;
    if (aux != NULL)
    {
        aux->e = object;
        aux->anterior = pos.pos;
        aux->siguiente = pos.pos->siguiente;
        if (pos.pos->siguiente != NULL)
        {
            pos.pos->siguiente->anterior = aux;
        }
        pos.pos->siguiente = aux;
        if (pos.pos == this->ultimo)
        {
            this->ultimo = aux;
        }
        return true;
    }
    return false;
}

bool TListaCom::Borrar(const TComplejo &object)
{
    TListaNodo *aux;
    bool encontrado = false;
    aux = this->primero;
    while (aux != NULL && !encontrado)
    {
        if (aux->e == object)
        {
            encontrado = true;
        }
        else
        {
            aux = aux->siguiente;
        }
    }
    if (encontrado)
    {
        if (aux->anterior != NULL)
        {
            aux->anterior->siguiente = aux->siguiente;
        }
        else
        {
            this->primero = aux->siguiente;
        }
        if (aux->siguiente != NULL)
        {
            aux->siguiente->anterior = aux->anterior;
        }
        else
        {
            this->ultimo = aux->anterior;
        }
        delete aux;
        return true;
    }
    return false;
}

bool TListaCom::BorrarTodos(const TComplejo &object)
{
    TListaNodo *aux;
    bool encontrado = false;
    aux = this->primero;
    while (aux != NULL)
    {
        if (aux->e == object)
        {
            encontrado = true;
            if (aux->anterior != NULL)
            {
                aux->anterior->siguiente = aux->siguiente;
            }
            else
            {
                this->primero = aux->siguiente;
            }
            if (aux->siguiente != NULL)
            {
                aux->siguiente->anterior = aux->anterior;
            }
            else
            {
                this->ultimo = aux->anterior;
            }
            delete aux;
            aux = this->primero;
        }
        else
        {
            aux = aux->siguiente;
        }
    }
    return encontrado;
}

bool TListaCom::Borrar(const TListaPos &pos)
{
    if (pos.pos != NULL)
    {
        if (pos.pos->anterior != NULL)
        {
            pos.pos->anterior->siguiente = pos.pos->siguiente;
        }
        else
        {
            this->primero = pos.pos->siguiente;
        }
        if (pos.pos->siguiente != NULL)
        {
            pos.pos->siguiente->anterior = pos.pos->anterior;
        }
        else
        {
            this->ultimo = pos.pos->anterior;
        }
        delete pos.pos;
        return true;
    }
    return false;
}

TComplejo TListaCom::Obtener(const TListaPos &pos) const
{
    if (pos.pos != NULL)
    {
        return pos.pos->e;
    }
    else
    {
        return TComplejo();
    }
}

bool TListaCom::Buscar(const TComplejo &object) const
{
    TListaNodo *aux;
    bool encontrado = false;
    aux = this->primero;
    while (aux != NULL && !encontrado)
    {
        if (aux->e == object)
        {
            encontrado = true;
        }
        else
        {
            aux = aux->siguiente;
        }
    }
    return encontrado;
}

int TListaCom::Longitud() const
{
    TListaNodo *aux;
    int cont = 0;
    aux = this->primero;
    while (aux != NULL)
    {
        cont++;
        aux = aux->siguiente;
    }
    return cont;
}

TListaPos TListaCom::Primera() const
{
    TListaPos aux;
    aux.pos = this->primero;
    return aux;
}

TListaPos TListaCom::Ultima() const
{
    TListaPos aux;
    aux.pos = this->ultimo;
    return aux;
}

ostream &operator<<(ostream &os, const TListaCom &lista)
{
    TListaPos aux;
    if (lista.EsVacia())
    {
        os << "{}";
    }
    else
    {
        os << "{";
        aux = lista.Primera();
        while (!aux.EsVacia())
        {
            os << lista.Obtener(aux);
            if (!aux.Siguiente().EsVacia())
            {
                os << " ";
            }
            aux = aux.Siguiente();
        }
        os << "}";
    }
    return os;
}
