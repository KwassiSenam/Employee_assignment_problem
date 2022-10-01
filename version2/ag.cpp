#include "ag.h"

#include <vector>
#include <chrono>

using namespace std;

// initialisation des paramètres de l'AG et génération de la population initiale
Ag::Ag(int d, int tp, double tcroisement, double tmutation, int tI)
{
	duree = d;
	taille_pop = tp;
	taux_croisement = tcroisement;
	taux_mutation = tmutation;
	taille_individu = tI;
	pop = new population(taille_pop);
}

// destructeur de l'objet
Ag::~Ag()
{
	delete pop;
}

// procédure principale de la recherche
individu* Ag::optimiser()
{
	int amelioration = 0;
	individu *fils1 = new individu();
	individu *fils2 = new individu();
	individu *pereX;
	individu *pereY;
	float best_fitness;

	// évaluation des individus de la population initiale
	for (int ind=0; ind<taille_pop; ind++)
	{
		pop->individus[ind]->evaluer();
	}

	// on ordonne les individus selon leur fitness
	pop->ordonner();

	best_fitness = pop->individus[pop->ordre[0]]->fitness;
	// on affiche les statistiques de la population initiale
	cout << "Quelques statistiques sur la population initiale" << endl;
	pop->statistiques();

	// tant que la durée d'execution n'est pas atteinte
	std::chrono::time_point<std::chrono::system_clock> start, end;

	int iteration = 0;
	start = std::chrono::system_clock::now();
	std::chrono::milliseconds mil(duree);
	while ((std::chrono::system_clock::now() - start) < mil)
	{
		cout<<"iteration = "<<iteration<<endl;
		iteration++;
		// sélection de deux individus de la population courante

		for (int i = 0; i < taux_croisement * taille_pop; i++) {
			pereX = pop->selection_roulette();
			pereY = pop->selection_roulette();
			if (pereX != pereY) {
				if (i % 2 == 0) {
					croisement1X(pereX, pereY, fils1, fils2);
				} else {
					croisement2X(pereX, pereY, fils1, fils2);
				}
				fils1->evaluer();
				fils2->evaluer();
				pop->remplacement_roulette(fils1);
				pop->remplacement_roulette(fils2);
			}
		}

		for (int i = 0; i < taux_mutation * taille_pop; i++) {
			pereX = pop->selection_aleatoire();
			pereX->mutation();
			pereX->evaluer();
		}


		// On réordonne la population selon la fitness
		pop->reordonner();

		// Si l'un des nouveaux indivudus-solutions est le meilleur jamais renconté
		if (pop->individus[pop->ordre[0]]->fitness < best_fitness)
		{
			best_fitness = pop->individus[pop->ordre[0]]->fitness;
			cout << "Amelioration de la meilleure solution a cet instant " << iteration << " : " << best_fitness << endl;
			amelioration = iteration;
		}
	}
	// on affiche les statistiques de la population finale
	cout << "Quelques statistiques sur la population finale" << endl;
	pop->statistiques();
	// on affiche la consanginité de la population finale
	pop->similitude();

	// retourner le meilleur individu rencontré pendant la recherche
	return pop->individus[pop->ordre[0]];
}

// opérateur de croisement à un point : croisement 1X
// 1) l'opérateur 1X choisit un point de croisement à midi d'un jour
// 2) l'opérateur 1X recopie le début du parent 1 au début de l'enfant 1
// et le début du parent 2 au début de l'enfant 2.
// 3) l'opérateur 1X complète l'enfant 1 avec les gènes manquant en les plaçant dans l'ordre du parent 2
// et l'enfant 2 avec les gènes manquant en les plaçant dans l'ordre du parent 1.
// Le 1ier fils est le produit de la partie haute du premier parent et
// de la partie basse du deuxième parent et inversement pour le 2ème fils
void Ag::croisement1X(individu* parent1, individu* parent2,
		individu* enfant1, individu* enfant2)
{

	std::vector<int> lst_tmp;
	for (int i=0; i < 11; i++)
	{
		lst_tmp.push_back(i);
	}

	bool succes = false;
	while (!lst_tmp.empty() && !succes) {
		int alea = Random::aleatoire(lst_tmp.size());
		int i;
		for (i = 0; i < Data::demi_journee[alea]; i++) {
			enfant1->genes[i] = parent1->genes[i];
			enfant2->genes[i] = parent2->genes[i];
		}
		for (; i < NBR_FORMATIONS; i++) {
			enfant1->genes[i] = parent2->genes[i];
			enfant2->genes[i] = parent1->genes[i];
		}

		i = 0;
		while (i < NBR_INTERFACES && !enfant1->is_valid(NBR_FORMATIONS - 1, i) && !enfant2->is_valid(NBR_FORMATIONS - 1, i)) {
			i++;
		}
		if (i < NBR_INTERFACES) {
			// Solution not valid
			lst_tmp.erase(lst_tmp.begin() + alea);
		} else {
			succes = true;
		}
	};


	if (!succes) {
		// Echec croisement
		return;
	}
}

void Ag::croisement2X(individu* parent1, individu* parent2,
		individu* enfant1, individu* enfant2)
{

	std::vector<int> lst_tmp;
	for (int i=0; i < 11; i++)
	{
		lst_tmp.push_back(i);
	}

	bool succes = false;
	while (!lst_tmp.empty() && !succes) {
		int alea = Random::aleatoire(lst_tmp.size());
		int begin = Data::demi_journee[alea - 1];
		int end = Data::demi_journee[alea];
		if (alea == 0) {
			begin = 0;
			end = Data::demi_journee[alea];
		}
		if (alea == 11) {
			begin = Data::demi_journee[alea];
			end = NBR_FORMATIONS;
		}

		if (end - begin == 0) {
			// Attention les fils seront identique
			//
			// Il y aurait la possibilité de relancer si le nombre de formations est suffisatment grand
		}

		int i;
		for (i = 0; i < begin; i++) {
			enfant1->genes[i] = parent1->genes[i];
			enfant2->genes[i] = parent2->genes[i];
		}
		for (; i < end; i++) {
			enfant1->genes[i] = parent2->genes[i];
			enfant2->genes[i] = parent1->genes[i];
		}
		for (; i < NBR_FORMATIONS; i++) {
			enfant1->genes[i] = parent1->genes[i];
			enfant2->genes[i] = parent2->genes[i];
		}

		i = 0;
		while (i < NBR_INTERFACES && !enfant1->is_valid(NBR_FORMATIONS - 1, i) && !enfant2->is_valid(NBR_FORMATIONS - 1, i)) {
			i++;
		}
		if (i < NBR_INTERFACES) {
			// Solution not valid
			lst_tmp.erase(lst_tmp.begin() + alea);
		} else {
			succes = true;
		}
	}

	if (!succes) {
		// Echec croisement
		return;
	}
}
