#include "population.h"
#include <limits>

using namespace std;

// initialisation d'une population de solutions
population::population(int tp)
{
	taille_pop = tp;
	individus = new individu*[taille_pop];
	for (int i=0; i<taille_pop; i++)
		individus[i] = new individu();
	ordre = new int[taille_pop];
}

// destruction de l'objet "population"
population::~population()
{
	for (int i=0; i<taille_pop; i++)
		delete individus[i];
	delete [] individus;
	delete [] ordre;
}

// statistiques sur la population
void population::statistiques()
{
	double moyenne = 0;
	double ecart_type = 0;

	for (int i=0; i<taille_pop; i++)
	{
		moyenne += individus[i]->fitness;
		ecart_type += individus[i]->fitness*individus[i]->fitness;
	}
	moyenne = moyenne / taille_pop;

	ecart_type = sqrt(ecart_type/taille_pop - moyenne*moyenne);
	ecart_type = ecart_type/taille_pop;

	cout << "fitness : (moyenne, ecart_type) -> ("
		<< moyenne << " , "  << ecart_type << ")" << endl;
	cout << "fitness : [meilleure, mediane, pire] -> ["
		<< individus[ordre[0]]->fitness << " , "
		<< individus[ordre[(int)(taille_pop/2)]]->fitness << " , "
		<< individus[ordre[taille_pop-1]]->fitness << "]" << endl;

}

// Similitude de la population
void population::similitude()
{
	int nb_ind_id_1, nb_ind_id_2, nb_ind_id_3;
	nb_ind_id_1 = nb_chromosomes_similaires(individus[ordre[0]]);
	cout << "Nombre d'indivudus de la population identique ayant la fitness = " << individus[ordre[0]]->fitness << " : " << nb_ind_id_1 << " / " << taille_pop << endl;
	if (nb_ind_id_1<taille_pop)
	{
		nb_ind_id_2 = nb_chromosomes_similaires(individus[ordre[nb_ind_id_1]]);
		cout << "Nombre d'indivudus de la population identique ayant la fitness = " << individus[ordre[nb_ind_id_1]]->fitness << " : " << nb_ind_id_2 << " / " << taille_pop << endl;
		if (nb_ind_id_1+nb_ind_id_2<taille_pop)
		{
			nb_ind_id_3 = nb_chromosomes_similaires(individus[ordre[nb_ind_id_1+nb_ind_id_2]]);
			cout << "Nombre d'indivudus de la population identique ayant la fitness = " << individus[ordre[nb_ind_id_1+nb_ind_id_2]]->fitness << " : " << nb_ind_id_3 << " / " << taille_pop << endl;
		}
	}
}

// compte le nombre de chromosomes similaires
int population::nb_chromosomes_similaires(individu* indiv)
{
	int nb = 0;
	for (int i=0; i<taille_pop; i++)
		if (indiv->identique_ind(individus[i]))
			nb++;
	return nb;
}

// Oronne les individus de la population par ordre croissant de fitness
void population::ordonner()
{
	int inter;
	for (int i=0; i<taille_pop; i++)
		ordre[i]=i;

	for (int i=0; i<taille_pop-1; i++)
		for (int j=i+1; j<taille_pop; j++)
			if(individus[ordre[i]]->fitness > individus[ordre[j]]->fitness)
			{
				inter = ordre[i];
				ordre[i] = ordre[j];
				ordre[j] = inter;
			}
}

// Ré-ordonne le classement des individus de la population par ordre croissant de fitness
// après un petit changement
void population::reordonner()
{
	int inter = 0;
	for (int i=0; i<taille_pop-1; i++)
		for (int j=i+1; j<taille_pop; j++)
			if(individus[ordre[i]]->fitness > individus[ordre[j]]->fitness)
			{
				inter = ordre[i];
				ordre[i] = ordre[j];
				ordre[j] = inter;
			}
}

// SELECTION PAR ROULETTE BIAISEE
// opérateur de sélection basé sur la fonction fitness
individu* population::selection_roulette()
{
	int somme_fitness = individus[0]->fitness;
	int fitness_max = individus[0]->fitness;
	int somme_portion = 0;

	for (int i=1; i<taille_pop; i++)
	{
		somme_fitness += individus[i]->fitness;
		if (fitness_max < individus[i]->fitness)
			fitness_max = individus[i]->fitness;
	}
	somme_portion = fitness_max*taille_pop - somme_fitness;
	// cout<<"somme_portion = "<<somme_portion<<endl;
	double variable_alea = Random::aleatoire(1000)/1000.0;

	int ind = 0;
	double portion = (fitness_max - individus[0]->fitness)*1./somme_portion;
	while ((ind<taille_pop-1) && (variable_alea>=portion))
	{
		ind++;
		portion += (fitness_max - individus[ind]->fitness)*1./somme_portion;
	}
	return individus[ind];
}

// opérateur de remplacement basé sur la roulette biaisée d'un individu de la population
// par un nouveau individu donné en argument
void population::remplacement_roulette(individu* indiv)
{
	int somme_fitness = individus[0]->fitness;
	// cout<<"Somme fitness = "<<somme_fitness<<endl;
	for (int i=1; i<taille_pop; i++)
		somme_fitness += individus[i]->fitness;

	double variable_alea;
	int ind = ordre[0];
	double portion;

	while (ordre[0]==ind)
	{
		variable_alea = Random::aleatoire(1000)/1000.0;
		ind = 0;
		portion = individus[0]->fitness*1./somme_fitness;
		while ((ind<taille_pop-1) && (variable_alea>portion))
		{
			ind++;
			portion += individus[ind]->fitness*1./somme_fitness;
		}
	}
	individus[ind]->copier(indiv);
	individus[ind]->fitness = indiv->fitness;
}

// SELECTION ALEATOIRE
// opérateur de sélection aléatoire
individu* population::selection_aleatoire()
{
	int ind_alea = Random::aleatoire(taille_pop);
	return individus[ind_alea];
}

// opérateur de remplacement alétoire d'un individu de la population
// par un nouveau individu donné en argument
void population::remplacement_aleatoire(individu* indiv)
{
	// cout<<"remplacement"<<endl;
	int ind_alea = Random::aleatoire(taille_pop);
	individus[ind_alea]->copier(indiv);
	individus[ind_alea]->fitness = indiv->fitness;
}

// affichage de la population, de son rang et de sa fitness
void population::afficher_pop()
{
	cout << "Population de " << taille_pop << " individus :" << endl;
	for (int i=0; i<taille_pop; i++)
	{
		cout << "individu " << i << ", rang : " << ordre[i] << " ";
		individus[i]->afficher();
	}
}
