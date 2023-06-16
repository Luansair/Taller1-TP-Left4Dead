# Informe TP1-Left4Dead-2D

## Alumnos

Pedro Gallino - 107587 - pgallino@fi.uba.ar

Luan Shair Corrionero - 102439 - lcorrionero@fi.uba.ar

-----------------------

## Instalacion / Dependencias

Tener en cuenta que esto es para Linux Ubuntu 22.04. Todavía no se probaron
otros SO.

### CMake

Indispensable para buildear, instalar e integrar otras librerias.

```shell
sudo apt-get install cmake
```

### SDL / SDL2 / SDL2pp

Necesario para las animaciones

Se descargan los siguientes archivos:
- libsdl2-image 2.6.3 https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3
- libsdl2-mixer 2.6.3 https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3
- libsdl2-ttf 2.20.2 https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2

Se instalan las dependencias

```shell
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev
```

Descomprimir los archivos descargados anteriormente y repetir estos pasos 
para cada uno.

```shell
cd carpeta_sdl_x
mkdir build 
cd build 
cmake .. 
make -j4
sudo make install
```

El siguiente paso es compilar e instalar la version 0.18.1 de libsdl2pp
Descargar el archivo: https://github.com/libSDL2pp/libSDL2pp/releases/tag/0.18.1
Descomprimir el archivo descargado

```shell
cd libSDL2pp-0.18.1
mkdir build 
cd build 
cmake .. 
make -j4
sudo make install
```

### Yaml

Necesario para leer los archivos de configuracion del juego y persistencia.

Se puede seguir el tutorial del repositorio: https://github.com/jbeder/yaml-cpp

Descargar el archivo: https://github.com/jbeder/yaml-cpp/releases/tag/yaml-cpp-0.7.0
Descomprimirlo
Dentro de la carpeta ejecutar

```shell
mkdir build
cd build
cmake ..
cmake --build .
```

Se puede remover el directorio `build` luego de instalarlo

-------------------------

## Build

Este paso es indispensable para crear los ejecutables, las pruebas, 
instaladores, entre otros.

El primer paso es crear la carpeta build para no tener los archivos creados por 
cmake dispersos en el proyecto. 
En la carpeta build se construye el ejecutable.

```shell
mkdir build
cd build
```

Luego, para generar todos los archivos se ejecutan los comandos:

```shell
cmake ..
cmake --build .
```

Este último paso debe repetirse si se desea que los cambios realizados en el 
proyecto tengan efecto. Esto volverá a generar la build a partir de los 
cambios.

**Chequear** que se está siempre dentro de la carpeta build antes de hacer 
cmake.

---

## Ejecucion del programa

Para ejecutar el programa hay que tener instalada **todas** las dependencias y 
haber **buildeado** el proyecto.

Dentro de la carpeta `build` abrir dos terminales:

En una de ellas ejecutar:
```shell
./Server 8080 #puede ser cualquier puerto válido
```

En la otra
```shell
./Client localhost 8080 #el puerto debe coincidir con el del server
```

Tambien puede usarse tiburoncin para ver los bytes que se envian entre ellos 
a través de sockets. 

Para ello se debe abrir una terminal mas en la **carpeta principal del proyecto**.

Luego:
```shell
#en una terminal en build
./Server 8082

#en la terminal de la carpeta principal
tiburoncin -f client0 -A :8081 -B :8082

#en la otra terminal en build
./Client 8081
```
Se debe respetar el orden. Los puertos pueden ser distintos, pero debe 
coincidir el A de tiburoncin con el del Cliente y el B con el del Server.


---

## Pruebas

Para ejecutar las pruebas hay que tener **todas** las 
dependencias y haber **buildeado** el proyecto.

Dentro del directorio `build` ejecutar:

```shell
ctest
```

Para una prueba en particular hay que moverse al directorio `tests`dentro de 
`build` y correr el ejecutable:

```shell
cd tests
./nombre_test
```


## Pre-commits

Para habilitar los pre-commits

```shell
pre-commit install
pre-commit install --hook-type commit-msg
```
Luego

```
git add <algo>
git commit
```
Se hace `git commit` sin `-m` para abrir el editor de texto y escribir un
commit que respete la convención establecida (commitizen). Se puede
deshabilitar borrando el hook.

Convencion: https://github.com/angular/angular/blob/22b96b9/CONTRIBUTING.md#-commit-message-guidelines

---

## Librerias utilizadas:

- SDL2pp: https://github.com/libSDL2pp/libSDL2pp
- yaml-cpp: https://github.com/jbeder/yaml-cpp
- thread.h, queue.h: https://github.com/eldipa/hands-on-threads/tree/master/libs
- GTest: https://github.com/google/googletest.git

---


