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

```shell
pre-commit install
pre-commit install --hook-type commit-msg
```
Primero se debe installar pre-commit y los hooks

```
git add <algo>
git commit
```
Se hace `git commit` sin `-m` para abrir el editor de texto y escribir un
commit que respete la convención establecida (commitizen). Se puede
deshabilitar borrando el hook.
