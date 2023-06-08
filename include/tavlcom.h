#ifndef _TAVLCOM_H
#define _TAVLCOM_H

#include <iostream>
#include <queue>
#include "tcomplejo.h"
#include "tvectorcom.h"
#include "tlistacom.h"

using namespace std;

class TNodoAVL;

class TAVLCom
{
    friend class TNodoAVL;

private:
    // Puntero al nodo raiz
    TNodoAVL *raiz;
    // AUXILIAR : Devuelve el recorrido en inorden
    void InordenAux(TVectorCom &, int &);
    // AUXILIAR : Devuelve el recorrido en preorden
    void PreordenAux(TVectorCom &, int &);
    // AUXILIAR : Devuelve el recorrido el postorden
    void PostordenAux(TVectorCom &, int &);
    // Borrar Auxiliar
    TNodoAVL *BorrarAux(TNodoAVL *n, const TComplejo &objeto);
    // Metodo auxiliar para BorrarAux
    TComplejo MayorMenores(TNodoAVL *n);
    TComplejo Encontrar_mayor_elemento();
    // Devuelve el arbol cuya raiz es el padre del TComplejo pasado
    TAVLCom Buscar_padre(const TComplejo &) const;
    // Devuelve si es hijo izquierdo
    bool es_hijo_izquierdo(const TComplejo objeto) const;
    // Devuelve si es hijo derecho
    bool es_hijo_derecho(const TComplejo objeto) const;
    // Devuelve si tiene hermano izquierdo
    bool tiene_hermano_izquierdo(const TComplejo objeto) const;
    // Devuelve si tiene hermano derecho
    bool tiene_hermano_derecho(const TComplejo objeto) const;

public:
    // FORMA CANONICA
    // Constructor por defecto
    TAVLCom();
    // Constructor de copia
    TAVLCom(const TAVLCom &);
    // Destructor
    ~TAVLCom();
    // Sobrecarga del operador asignacion
    TAVLCom &operator=(const TAVLCom &);
    // METODOS
    // Sobrecarga del operador igualdad
    bool operator==(const TAVLCom &);
    // Sobrecarga del operador desigualdad
    bool operator!=(const TAVLCom &);
    // Devuelve TRUE si el árbol está vacio, FALSE en caso contrario
    bool EsVacio() const;

    void RotacionDD();
    void RotacionDI();
    void RotacionII();
    void RotacionID();
    // Inserta el elemento en el arbol
    bool Insertar(const TComplejo &);
    bool InsertarAux(const TComplejo&, bool&);
    // Borra el elemento en el arbol
    bool Borrar(const TComplejo &);
    bool Borrar(const TComplejo &, bool &);
    // Devuelve TRUE si el elemento esta en el arbol, FALSE en caso contrario
    bool Buscar(const TComplejo &) const;
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

    // Devuelve entre 1 y 5 dependiendo de cositas
    int* HijosAVL (const TListaCom &);
    // Si existe el elemento y es par devuelve su recorriedo al extremo derecho si no izquierdo y si no existe devuelve un TComplejo(0,0)
    TListaCom Caminos_AVL (TVectorCom & );
    // Recorrido al extremo derecho desde TComplejo
    TListaCom Caminos_AVL_recorrido_derecha (TComplejo & );
    // Recorrido al extremo izquierdo desde TComplejo
    TListaCom Caminos_AVL_recorrido_izquierda (TComplejo & );
    // Devuelve arbol en el que el apdre es el TComplejo
    TAVLCom Encontrar_arbol_nodo(TComplejo &);
    //Devuelve 0,1,2,3
    int*  BuscaAVL (TListaCom &);

    // Sobrecarga del operador salida
    friend ostream &operator<<(ostream &, const TAVLCom &);
};

class TNodoAVL
{
    friend class TAVLCom;

private:
    // El elemento del nodo
    TComplejo item;
    // Subarbol izquierdo y derecho
    TAVLCom iz, de;
    // Factor de equilibrio
    int fe;

public:
    // Constructor por defecto
    TNodoAVL();
    // Constructor de copia
    TNodoAVL(const TNodoAVL &);
    // Destructor
    ~TNodoAVL();
    // Sobrecarga del operador asignacion
    TNodoAVL &operator=(const TNodoAVL &);
};

#endif