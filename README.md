# Informe del tp1

Pedro Gallino - 107587 - pgallino@fi.uba.ar

Franco Daniel Capra - 99642 - fcapra@fi.uba.ar

Luan Shair Corrionero - 102439 - lcorrionero@fi.uba.ar

## ¡Cambiar a branch dev para desarrollo!

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

## Pruebas

Todavía no está bien armado y es medio complicado. Las pruebas están en el 
directorio *build/tests*. Actualmente se llaman 'resolver_test' y para 
ejecutarlas hay que hacer `./resolver_test`

La complicación es que para añadir mas pruebas hay que agregar al ejecutable 
los .cpp de los tests y los .cpp de todos los archivos que necesiten para 
ejecutarse.

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

## Librerias utilizadas:

- SDL2pp: https://github.com/libSDL2pp/libSDL2pp
- yaml-cpp: https://github.com/jbeder/yaml-cpp
- thread.h, queue.h: https://github.com/eldipa/hands-on-threads/tree/master/libs
- GTest: https://github.com/google/googletest.git
- 
## Protocolo

### Propuesta 1: inputs directos

El cliente envía los inputs directamente, que son ints, al servidor.
Entonces el servidor transforma esos inputs en acciones y hace algo.

#### Ventajas: 

- fácil de hacer porque no hay que parsear nada desde el cliente.
- lógica mínima de parte del cliente.

#### Desventajas: 

- el server debe conocer qué significan los ints.
- el usuario no puede configurar sus controles o bien el server debe conocer la configuración de cada usuario.

### Propuesta 2: acciones parseadas

El cliente parsea los inputs a acciones. El servidor interpreta estas
acciones y hace algo.

#### Ventajas:

- quizá mas intuitivo.
- el cliente puede tener su propia configuración de teclado y mouse

#### Desventajas:

- mayor lógica en el cliente.
- implementar mas objetos en el cliente.
- el server debe parsear la acción de todas formas.

## Estructura del proyecto (reveer)

Es posible que haga falta una reestructuración.

En Common están los archivos utilizados para compilar tanto Server como Client.
Se dividen en src/ (donde están los .cpp) e include/ (donde están los .h).

En Server están los archivos para compilar Server y en Client lo mismo.
Internamente tienen la misma división que Common. Se pueden agregar carpetas
con información específica que requiere cada uno.

Las pruebas están en una carpeta a parte y su estructura está por verse.

Las librerías tambien tienen su propio directorio.

Los recursos (por ahora) tienen su propio directorio.

Hay archivos con el mismo nombre para Server y Client (pero el código es
distinto) por lo que las pruebas podría tener conflictos.