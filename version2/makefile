# Dans les makefile, on commence usuellement par définir des macros. 
# Si vous écrivez dans ce fichier :
#     TOTO= titi tutu tata
# ou ce qui est équivalent mais plus beau à voir :
#     TOTO= titi \
#     <tab> tutu \
#     <tab> tata 
# make remplacera tous les $(TOTO) qu'il rencontrera dans la suite du
# fichier par :	
#     titi tutu tata

# Donc on y va pour la définition préalable de quelques macros

# Les librairies que l'on va utiliser
LIBS= -lm

# Les endroits où on peut trouver des librairies
LIBS_PATH= \
	-L/lib \
	-L/usr/lib \
	-L/usr/local/lib

# Le compilateur que nous utiliserons
COMPILO=g++

# Les options de compilation des sources
#    -c    : Ne fait pas un exécutable, mais seulement un .o
#    -g    : Fait un objet débuggable
#    -Wall : Affiche un maximum de warnings si le code C++ est douteux
#    -ansi : Assure que le code C++ suit la norme ANSI, et est donc portable.
FLAGS= -O3 -Wall -c

# Liste des objets que l'on va obtenir, et qu'il faudra linker.
OBJ=    main.o \
	ag.o \
	individu.o \
	population.o





# Après avoir défini les macro, on définit des cibles. Une cible est une expression
# du style :
#   <nom> : <dep1> <dep2> ... <depn>
#   <tab> : <commande>
#
# Pour que make exécute une cible <nom>, il faut taper à l'endroit où se trouve le makefile
#   make <nom>
# Si on ne donne pas de <nom>, la première cible est exécutée.
# L'exécution de la cible <nom> se déroule comme suit :
#   Pour chacun des <depi>, regarder si <depi> n'est pas un nom de fichier.
#     Si <depi> n'est pas un nom de fichier
#        Alors exécuter la cible <depi> (qui doit être définie dans ce fichier makefile)
#              puis exécuter <commande>
#     Si <depi> est un fichier 
#        Si il est a jour (sa date est antérieur à la date de la dernière commande make)
#           Ne rien faire
#        Si il n'est pas a jour et qu'il existe une cible <depi>, l'exécuter
#              puis exécuter <commande>
#        Si il n'est pas a jour et qu'il n'existe pas de cible <depi>
#               exécuter <commande>.
#
# Ce mécanisme permet, entre autre chose, de ne recompiler que les objets dont le source
# C++ correspondant à été modifié.

######################
#                    #
# Cibles Principales #
#                    #
######################


# Pour compiler coup_de_vent, il faut vérifier que tous les .o
# sont à jour (les recompiler dans le cas contraire) puis lancer
# la commande de linkage.
algo_evo : $(OBJ)
	$(COMPILO) -o algo_evo -g $(OBJ) $(LIBS_PATH) $(LIBS)

###########################
#                         #
# Compilation des sources #
#                         #
###########################

# Source bidon, bien utile pour faire des copier-coller et obtenir les suivantes
# par en remplacement de xx.
# Le sens est que xx.o s'obtent à partir de xx.cc (la seule dépendance ici) quand
# le fichier xx.cc vient d'être modifié
%.o : %.cpp
	$(COMPILO) $(FLAGS) $< -o $@

#xx.o : xx.cc
#	$(COMPILO) $(FLAGS) $(INCLUDE_PATH) -o xx.o xx.cc


.PHONY: clean clear
# Taper 'make clean' provoque l'effacement de tous les .o, et des *~ laissés 
# par emacs. Il n'y a pas de dépendence pour cette cible.
clean : 
	rm -f *.o *~

# Taper 'make clear' fait un 'make clean' puis efface en plus l'exécutable.
clear : 
	make clean;
	rm -f algo_evo

