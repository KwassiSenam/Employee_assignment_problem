#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include "random.h"
#include "data.h"

// La classe chromosome represente la structure d'une solution du problème
class individu{
public:
    // ATTRIBUTS
	int *genes; // les gènes de l'individu = solution
	int taille; // la taille de l'individu = nombre de formations
	double distance_totale;
	double distance_interfaces[NBR_INTERFACES];
	int nbr_trajets[NBR_INTERFACES];
	double f_corr;
	double moy; //distance moyenne parcourue pour une solution donnée s(ici individu)
	int pen; // nombre de spécialités non satisfaites
	double ecart; //écart-type des distances pour une solution donnée
	double fitness; // le fitness(valeur de la fonction objectif ) de la solution

	// CONSTRUCTEURS
	individu(); // constructeur de l'objet aléatoirement
	~individu(); // destructeur de l'objet

	// METHODES
	void afficher(); // fonction d'affichage de la solution
	void reparer(); // permet de réduire le nombre d'heures d'une interface si celle-ci depasse son nombre d'heures limite de travail
	void evaluer();
	bool mutation(void);
	bool is_valid(int position, int valeur); // renvoie "true" si l'ensemble des contraintes est respecté
	// fonction d'évaluation de l'individu (fonction objectif)
	// Elle doit etre lancée à la creation des solution et apres
	// l'exécution des operateurs de mutation et de croisement
	double moyenne();
	double ecart_type(double m);
	int penalite();
	void copier(individu* source); // copie l'individu 'source'
	bool identique_ind(individu* indiv); // test si 2 individus sont identiques

	// OPERATEURS DE MUTATION
	void echange_2_genes(int gene1,int gene2); // interchange 2 gènes d'un individu;
	void echange_2_genes_consecutifs(); // interchange 2 gènes consécutifs d'un individu
	void echange_2_genes_quelconques(int i, int j); // interchange aléatoirement 2 gènes d'un individu

};

# endif
