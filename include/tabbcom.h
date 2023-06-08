#ifndef _TABBCOM_H
#define _TABBCOM_H

#include <iostream>
#include <queue>
#include "tcomplejo.h"
#include "tvectorcom.h"
#include "tlistacom.h"

using namespace std;

class TNodoABB;

class TABBCom
{
    friend class TNodoABB;

private:
    // Puntero al nodo
    TNodoABB *nodo;
    // AUXILIAR : Devuelve el recorrido en inorden
    void InordenAux(TVectorCom &, int &);
    // AUXILIAR : Devuelve el recorrido en preorden
    void PreordenAux(TVectorCom &, int &);
    // AUXILIAR : Devuelve el recorrido el postorden
    void PostordenAux(TVectorCom &, int &);
    // Borrar Auxiliar
    TNodoABB *BorrarAux(TNodoABB *n, const TComplejo &objeto);
    // Metodo auxiliar para BorrarAux
    TComplejo MayorMenores(TNodoABB *n);

public:
    // FORMA CANONICA
    // Constructor por defecto
    TABBCom();
    // Constructor de copia
    TABBCom(const TABBCom &);
    // Destructor
    ~TABBCom();
    // Sobrecarga del operador asignacion
    TABBCom &operator=(const TABBCom &);
    // METODOS
    // Sobrecarga del operador igualdad
    bool operator==(const TABBCom &);
    // Devuelve TRUE si el árbol está vacio, FALSE en caso contrario
    bool EsVacio() const;
    // Inserta el elemento en el arbol
    bool Insertar(const TComplejo &);
    // Borra el elemento en el arbol
    bool Borrar(const TComplejo &);
    // Devuelve TRUE si el elemento esta en el arbol, FALSE en caso contrario
    bool Buscar(const TComplejo &);
    // Devuelve el elemento en la raiz del arbol
    TComplejo Raiz();
    // Devuelve la altura del arbol (la altura de un arbol vacio es 0)
    int Altura();
    // Devuelve el numero de nodos del arbol (un arbol vacio posee 0 nodos)
    int Nodos() const;
    // Devuelve el numero de nodos hoja en el arbol (la raiz puede ser nodo hoja)
    int NodosHoja();

    // Devuelve el recorrido en inorden
    TVectorCom Inorden();
    // Devuelve el recorrido en preorden
    TVectorCom Preorden();
    // Devuelve el recorrido en postorden
    TVectorCom Postorden();
    // Devuelve el recorrido en niveles
    TVectorCom Niveles() const;

    // Recibe una lista de TComplejos, si existen no hace nada, si no existen los introduce al arbol y concatena al return el vector con el camino de la raiz al nodo insertado
    TVectorCom ABBCamino (const TListaCom &);
    // Metodo auxiliar que devuelve el recorrido entre 2 TComplejos (NO FIABLE)
    TVectorCom ABBCamino_aux(const TComplejo &, const TComplejo &);
    // Devuelve el todos los niveles de los elementos de la lista
    TComplejo* MostrarNiveles (TListaCom  & );
    // Devuelve el nivel elejido por parametro
    TVectorCom Nivel_aux(const int & ,const TABBCom &);
    // Devuelve true o false si el TComplejo minimo y maximo tienen un camino entre ellos
    bool examen(TListaCom &);
    // Devuelve el arbol correspendiente al TComplejo como raiz
    TABBCom Encontrar_arbol_nodo(TComplejo &);
    // Devuelve un vector de enteros de 1 o 0 si existe camino entre el primer y el primer elemento
    int *Multicamino (TListaCom & , TListaCom &);

    // Sobrecarga del operador salida
    friend ostream &operator<<(ostream &, const TABBCom &);
};

class TNodoABB
{
    friend class TABBCom;

private:
    // El elemento del nodo
    TComplejo item;
    // Subarbol izquierdo y derecho
    TABBCom iz, de;

public:
    // Constructor por defecto
    TNodoABB();
    // Constructor de copia
    TNodoABB(const TNodoABB &);
    // Destructor
    ~TNodoABB();
    // Sobrecarga del operador asignacion
    TNodoABB &operator=(const TNodoABB &);
};

#endif