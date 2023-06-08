#!/bin/bash

# Nombres de archivo
file_names=(TABBCom-01 TABBCom-02 TABBCom-03 TABBCom-04 TABBCom-05 TABBCom-06 TABBCom-07 TABBCom-08 TABBCom-09 TABBCom-10)

# Si se proporciona un argumento "main", copiar y compilar solo main.cpp
if [ "$1" == "main" -o "$1" == "all" ]; then
  cp "./lib/tcomplejo.cpp" .
  cp "./include/tcomplejo.h" .
  cp "./lib/tvectorcom.cpp" .
  cp "./include/tvectorcom.h" .
  cp "./include/tlistacom.h" .
  cp "./lib/tlistacom.cpp" .
  cp "./lib/tabbcom.cpp" .
  cp "./include/tabbcom.h" .
  cp "./src/tad.cpp" .
  g++ -Wall tcomplejo.cpp tcomplejo.h tvectorcom.cpp tvectorcom.h tlistacom.cpp tlistacom.h tabbcom.cpp tabbcom.h tad.cpp -o aaa && ./aaa
  rm tcomplejo.cpp tcomplejo.h tvectorcom.cpp tvectorcom.h tlistacom.cpp tlistacom.h tabbcom.cpp tabbcom.h tad.cpp aaa 
  echo "Compilación completada"
  if [ "$1" == "main" ]; then
    exit 0
  fi
fi

# Si se proporciona un argumento, ejecutar solo ese test
if [ "$1" != "all" ];then
  if [ $# -eq 1 ]; then
    name="TABBCom-$1"
    if [[ ! " ${file_names[@]} " =~ " ${name} " ]]; then
      echo "Error: test $1 no encontrado"
      exit 1
    fi
    file_names=($name)
  fi
fi

# Copiar archivos de programa
  cp "./lib/tcomplejo.cpp" .
  cp "./include/tcomplejo.h" .
  cp "./lib/tvectorcom.cpp" .
  cp "./include/tvectorcom.h" .
  cp "./lib/tlistacom.cpp" .
  cp "./include/tlistacom.h" .
  cp "./lib/tabbcom.cpp" .
  cp "./include/tabbcom.h" .

# Recorrer los nombres de archivo
for name in "${file_names[@]}"; do
  # Copiar los archivos necesarios
  cp "./test/TADs_prueba_cuadernillo_2/${name}.cpp" .
  cp "./test/TADs_prueba_cuadernillo_2/${name}.cpp.sal" .

  # Compilar el código
  g++ -Wall tcomplejo.cpp tcomplejo.h tvectorcom.cpp tvectorcom.h tlistacom.cpp tlistacom.h tabbcom.cpp tabbcom.h "${name}.cpp" -o aaa

  # Comprobar si la salida de aaa es igual a ${name}.cpp.sal
  if diff -q "${name}.cpp.sal" <(./aaa); then
    echo "Test ${name} passed"
  else
    echo "Test ${name} failed"
    echo "Differences for ${name}:"
    diff "${name}.cpp.sal" <(./aaa)
  fi

  # Eliminar los archivos copiados
  rm "${name}.cpp" "${name}.cpp.sal" aaa 
done

# Eliminar los archivos de programa
rm tcomplejo.cpp tcomplejo.h tvectorcom.cpp tvectorcom.h tlistacom.cpp tlistacom.h tabbcom.cpp tabbcom.h
