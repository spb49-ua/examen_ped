#include <iostream>
#include "tabbcom.h"
#include "tcomplejo.h"
#include "tvectorcom.h"
#include "tlistacom.h"
using namespace std;

int
main(void)
{
  
  TABBCom a;

  a.Insertar(TComplejo(6, 0));
  a.Insertar(TComplejo(3, 0));
  a.Insertar(TComplejo(8, 0));
  a.Insertar(TComplejo(1, 0));
  a.Insertar(TComplejo(5, 0));
  a.Insertar(TComplejo(7, 0));
  a.Insertar(TComplejo(10, 0));
  
  TListaCom lista1;
  lista1.InsCabeza(TComplejo(3,0));

  TListaCom lista2;
  lista2.InsCabeza(TComplejo(25,0));
  lista2.InsCabeza(TComplejo(9,0));
  lista2.InsCabeza(TComplejo(8,0));
  lista2.InsCabeza(TComplejo(6,0));
  lista2.InsCabeza(TComplejo(1,0));

  TListaCom lista3;
  lista3.InsCabeza(TComplejo(25,0));
  lista3.InsCabeza(TComplejo(10,0));
  lista3.InsCabeza(TComplejo(8,0));
  lista3.InsCabeza(TComplejo(6,0));
  lista3.InsCabeza(TComplejo(1,0));

  TListaCom lista4;
  lista4.InsCabeza(TComplejo(10,0));
  lista4.InsCabeza(TComplejo(8,0));
  lista4.InsCabeza(TComplejo(7,0));
  lista4.InsCabeza(TComplejo(5,0));
  lista4.InsCabeza(TComplejo(1,0));



  int * test1 = a.Multicamino(lista1,lista2);
  int * test2 = a.Multicamino(lista3,lista4);

  cout << "[";
  for (int i = 0; i < max(lista1.Longitud(),lista2.Longitud()); i++)
  {
    cout << test1[i] << ",";
  }
  cout << "]"<<endl;

  cout << "[";
  for (int i = 0; i < max(lista3.Longitud(),lista4.Longitud()); i++)
  {
    cout << test2[i] << ",";
  }
  cout << "]";


  return 1;
}
