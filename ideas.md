![img.png](https://plantuml-server.kkeisuke.dev/svg/XP11IyH038NlyojoKw6rzs9bGMzUbbty0MCREmCpcJ79M1Rnlpjso-91yVJWvUCbBpjHorfYC5TEDKlVTJbO-dPknnGxmRU2D68xUJkpZSROeebAV44s3y4ZQNj_H7v7xjdFJf_mz9WMscPtRRiDQ-e9-QXMYy007pb90ruEXSZJF2WNR63oFAmf3Q2EdvS5P-qPQKBUhqdNFmDl32L5I7KHR2oeymBYKWaJMFBHLa0TGgnKh0GKKXzMIzOJAoLBbSMh0mkYAV_Ly3cRizDURlkdtwiDyal1NMrKN_q5.svg)
Puede que para resolver las colisiones desde el server no haga falta una matriz. Con que sepa el tamaño de los sprites y la posicion inicial de cada elemento alcanza. 

No sé como se sincronizará los jugadores con el server (sera tema de performance). Las acciones modificarían la partida "desde fuera" y partida en su loop haria el update 

Actualizar el readme con los pasos para instalar
Documentacion: 3 pdfs. 
1 con el manual de usuario (imagenes del juego): explicar un usuario q no sabe nada para instalar el juego y como jugarlo
2 documentacion tecnica: diagramas, protocolos, modelado de commands, los hilos.
3 manual de proyecto: reflexión de la materia y el trabajo en general
Crear un instalador

Hacer un lobby, se puede hacer por terminal (sin QT o algo de QT)
Hacer primero la camara, background y suelo.
LA camara debe estar hecha en el cliente usando las posiciones de los jugadores.
El centro de masa siempre esta en ancho/2 y altura/2 (centro de la pantalla)
La camara solo se movera hacia los costados y se calcula en cada frame de acuerdo a las posiciones de los jugadores.
Ver truco para el background en internet
El background depende del mapa por lo que esa info se brinda al server (background 1, 2 ,3).
Adaptar el protocolo a las nuevas modificaciones. 

El suelo es en el server.

-----

Para desacoplar el protocolo del Server se puede crear un RequestDTO, un InGameCommandFactory y un Request Code donde
las request ingame vayan del 0 en adelante (mismo puede pasar para las pre game).

El Factory tiene un array con objetos Builder.
Cada builder sabe 'buildCommand' pero devuelve un comando distinto.
Factory solo obtiene el player_id y el DTO.

Es bastante trabajo dado que hay que crear un RequestDTO y un Builder para cada comando.
Despues hacer un dynamic cast del RequestDTO para obtener los datos del mismo.

De esta manera el protocolo no necestaria recibir playerID

En el cliente para serializar protocolo puede tener como atributo un Serializer para
serializar numeros de 2 y 4 bytes.

-------

Modularizar protocolo servidor.

Protocolo servidor deberia devolver un puntero inteligente.


-------------

Para acceder a los elementos creados desde QCreator hay que ir a ui_lobbywindow.h.
Se accede con ui->nombre_elemento

---------

manual de usuario imagenes e instrucciones
manual tecnico, mostrar 5 o 6 diagramas