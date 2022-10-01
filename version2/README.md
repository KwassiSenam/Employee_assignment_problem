##Initialement
Lancer les commandes chmod +x build et chmod +x run

### Compilation

Le programme se compile en executant le fichier ./build

### Execution

Le programme s'execute en lançant le fichier ./run


### Paramétrage

Le parametre de temps d'execution du programme est modifiable dans le main.cpp

* Le temps d'execution du programme en ms (variable "duree")

Les interfaces (spécialité), les formations, lieux de formations et leur contenu sont dans le main.cpp

* Des variables qui appartiennent à la classe "statique" Data sont modifiables. Leur taille en revanche est accessible uniquement dans "data.h"

Le nombre d'interfaces dans le tableau (NBR\_INTERFACES\_TOTAL), le nombre d'interfaces utilisée (NBR\_INTERFACES) sont à modifier dans les directives préprocesseur de "data.h"
De même pour les formations (NBR\_FORMATIONS) et le nombre de formations du tableau (NBR\_FORMATIONS\_TOTAL).

ATTENTION : Bien utiliser ./build pour recompiler le programme après le changement d'un des paramètres
--------
