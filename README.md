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