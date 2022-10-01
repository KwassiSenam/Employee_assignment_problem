#ifndef _AG_H
#define _AG_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "population.h"

using namespace std;
// La classe Ag d�finie les param�tres d'une ex�cution d'un algorithme
//    �volutionniste ainsi que la proc�dure principale de recherche
class Ag{
public:
    // ATTRIBUTS
	int duree;       // duree de la recherche de la meilleure solution(duree en min)
	int taille_pop;          // nombre d'individus dans la population
	double taux_croisement;  // taux de croisement : valeur entre 0 et 1
	double taux_mutation;    // taux de mutation : valeur entre 0 et 1
	int taille_individu;   // nombre de g�nes dans l'individu
	population *pop;         // liste des individus de la population

	// CONSTRUCTEURS
	Ag(int d, int tp, double tcroisement, double tmutation, int tI);
                             // constructeur de l'objet
	~Ag();                   // destructeur de l'objet

	// METHODES
	individu* optimiser(); // fonction principale qui d�roule l'algorithme

	// OPERATEURS DE CROISEMENT
	// op�rateur de croisement 1X de deux individus
    void croisement1X(individu* parent1, individu* parent2,
                      individu* enfant1, individu* enfant2);
    void croisement2X(individu* parent1, individu* parent2,
                      individu* enfant1, individu* enfant2);
};

# endif
