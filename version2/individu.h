#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include "random.h"
#include "data.h"

// La classe chromosome represente la structure d'une solution du probl�me
class individu{
public:
    // ATTRIBUTS
	int *genes; // les g�nes de l'individu = solution
	int taille; // la taille de l'individu = nombre de formations
	double distance_totale;
	double distance_interfaces[NBR_INTERFACES];
	int nbr_trajets[NBR_INTERFACES];
	double f_corr;
	double moy; //distance moyenne parcourue pour une solution donn�e s(ici individu)
	int pen; // nombre de sp�cialit�s non satisfaites
	double ecart; //�cart-type des distances pour une solution donn�e
	double fitness; // le fitness(valeur de la fonction objectif ) de la solution

	// CONSTRUCTEURS
	individu(); // constructeur de l'objet al�atoirement
	~individu(); // destructeur de l'objet

	// METHODES
	void afficher(); // fonction d'affichage de la solution
	void reparer(); // permet de r�duire le nombre d'heures d'une interface si celle-ci depasse son nombre d'heures limite de travail
	void evaluer();
	bool mutation(void);
	bool is_valid(int position, int valeur); // renvoie "true" si l'ensemble des contraintes est respect�
	// fonction d'�valuation de l'individu (fonction objectif)
	// Elle doit etre lanc�e � la creation des solution et apres
	// l'ex�cution des operateurs de mutation et de croisement
	double moyenne();
	double ecart_type(double m);
	int penalite();
	void copier(individu* source); // copie l'individu 'source'
	bool identique_ind(individu* indiv); // test si 2 individus sont identiques

	// OPERATEURS DE MUTATION
	void echange_2_genes(int gene1,int gene2); // interchange 2 g�nes d'un individu;
	void echange_2_genes_consecutifs(); // interchange 2 g�nes cons�cutifs d'un individu
	void echange_2_genes_quelconques(int i, int j); // interchange al�atoirement 2 g�nes d'un individu

};

# endif
