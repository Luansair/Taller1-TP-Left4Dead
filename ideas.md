![img.png](https://plantuml-server.kkeisuke.dev/svg/XP11IyH038NlyojoKw6rzs9bGMzUbbty0MCREmCpcJ79M1Rnlpjso-91yVJWvUCbBpjHorfYC5TEDKlVTJbO-dPknnGxmRU2D68xUJkpZSROeebAV44s3y4ZQNj_H7v7xjdFJf_mz9WMscPtRRiDQ-e9-QXMYy007pb90ruEXSZJF2WNR63oFAmf3Q2EdvS5P-qPQKBUhqdNFmDl32L5I7KHR2oeymBYKWaJMFBHLa0TGgnKh0GKKXzMIzOJAoLBbSMh0mkYAV_Ly3cRizDURlkdtwiDyal1NMrKN_q5.svg)
Puede que para resolver las colisiones desde el server no haga falta una matriz. Con que sepa el tamaño de los sprites y la posicion inicial de cada elemento alcanza. 

Al recibir acciones mueve los sprites y calcula colisiones etc.

Partida me parece q tambien va a tener su game loop porque si los players no hacen nada los zombies tienen que seguir moviendose y enviar feedback.

No sé como se sincronizará los jugadores con el server (sera tema de performance). Las acciones modificarían la partida "desde fuera" y partida en su loop haria el update 