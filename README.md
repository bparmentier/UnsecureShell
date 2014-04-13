UnsecureShell
=============

Haute École de Bruxelles - École Supérieure d'Informatique

Projet IPC051 - Systèmes d'exploitation - 2013-2014

Simple shell client-serveur en C avec sockets.

Usage
-----
`make` dans le répertoire principal produit le rapport au format PostScript.
`make` dans le répertoire SOURCES produit un exécutable et lance une
démonstration.

Les adresses IP sont hardcodées (127.0.0.1 par défaut). Lancer `ShellServeur`
puis `ShellClient`. De nombreux bugs sont encore présents (par exemple, le
client bloque lorsque la commande exécutée de renvoie rien...).

Dépendances
-----------
gcc, latex, gv
