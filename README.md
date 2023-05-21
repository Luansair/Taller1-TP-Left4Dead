# Informe del tp1

Pedro Gallino - 107587 - pgallino@fi.uba.ar

Franco Daniel Capra - 99642 - fcapra@fi.uba.ar

Luan Shair Corrionero - 102439 - lcorrionero@fi.uba.ar

## Build
```shell
mkdir build
cd build
cmake ..
cmake --build .
```
Se crea la carpeta build para no tener los archivos creados por cmake dispersos
en el proyecto. En la carpeta build se construye el ejecutable.
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