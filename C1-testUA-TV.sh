#!/bin/bash

# Nombres de archivo
file_names=(tad01 tad02 tad03 tad04 tad05 tad06 tad07 tad08 tad09 tad10 tad11 tad12)

# Si se proporciona un argumento "main", copiar y compilar solo main.cpp
if [ "$1" == "main" -o "$1" == "all" ]; then
  cp "./lib/tcomplejo.cpp" .
  cp "./lib/tvectorcom.cpp" .
  cp "./include/tcomplejo.h" .
  cp "./include/tvectorcom.h" .
  cp "./src/main2.cpp" .
  g++ -Wall tcomplejo.cpp tcomplejo.h tvectorcom.cpp tvectorcom.h main2.cpp -o bbb && ./bbb
  rm tcomplejo.cpp tcomplejo.h tvectorcom.cpp tvectorcom.h main2.cpp bbb
  echo "Compilación completada"
  if [ "$1" == "main" ]; then
    exit 0
  fi
fi

# Si se proporciona un argumento, ejecutar solo ese test
if [ "$1" != "all" ];then
  if [ $# -eq 1 ]; then
    name="tad$1"
    if [[ ! " ${file_names[@]} " =~ " ${name} " ]]; then
      echo "Error: test $1 no encontrado"
      exit 1
    fi
    file_names=($name)
  fi
fi

# Copiar archivos de programa
cp "./lib/tcomplejo.cpp" .
cp "./lib/tvectorcom.cpp" .
cp "./include/tcomplejo.h" .
cp "./include/tvectorcom.h" .

# Recorrer los nombres de archivo
for name in "${file_names[@]}"; do
  # Copiar los archivos necesarios
  cp "./test/TADs_prueba_cuadernillo_1/TVectorCom_PRUEBA/${name}.cpp" .
  cp "./test/TADs_prueba_cuadernillo_1/TVectorCom_PRUEBA/${name}.cpp.sal" .

  # Compilar el código
  g++ -Wall tcomplejo.cpp tcomplejo.h tvectorcom.cpp tvectorcom.h "${name}.cpp" -o bbb

  # Comprobar si la salida de aaa es igual a ${name}.cpp.sal
  if diff -q "${name}.cpp.sal" <(./bbb); then
    echo "Test ${name} passed"
  else
    echo "Test ${name} failed"
    echo "Differences for ${name}:"
    diff "${name}.cpp.sal" <(./bbb)
  fi

  # Eliminar los archivos copiados
  rm "${name}.cpp" "${name}.cpp.sal" bbb 
done

# Eliminar los archivos de programa
rm tcomplejo.cpp tcomplejo.h tvectorcom.cpp tvectorcom.h 
