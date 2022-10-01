#ifndef POPULATION_H
#define POPULATION_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include "individu.h"

// La classe population englobe plusieurs solution potentielle du probleme
class population{
public:
    // ATTRIBUTS
	individu **individus;  // liste des individus de la population
	int taille_pop;          // nombre d'individus de la population
	int *ordre;              // tableau donnant l'ordre des individus dans la population
                             //   du meilleur au plus mauvais en fonction de la fitness	population(int tp, int tc);    // constructeur de l'objet

	// CONSTRUCTEURS
	population(int tp); // constructeur de l'objet
	~population();              // destructeur de l'objet

	// METHODES
	void statistiques(); // affiche quelques statistiques sur la population
	int nb_chromosomes_similaires(individu* indiv);
	                     // compte le nombre d'individu similaires à 'indiv'
	void similitude();   // affiche les résultats du comptage d'individus similaires
	                     // aux meilleurs individus de la population.

    // OPERATEURS DE SELECTION ET DE REMPLACEMENT
    individu *selection_roulette();                 // seléction par roulette biaisée d'un individu de la population
    void remplacement_roulette(individu* indiv); // remplacement par roulette biaisée d'un individu de la population par un 'indiv' donné

    individu *selection_ranking(float taux_ranking);// seléction par ranking d'un individu de la population
    void remplacement_ranking(individu* indiv, float taux_ranking); // rempacement par ranking d'un individu de la population par un 'indiv' donné

    individu* selection_aleatoire();                // sélection alétoire
    void remplacement_aleatoire(individu* indiv);// remplacement alétoire

    void ordonner();
    void reordonner();
    void afficher_pop();
};

# endif
