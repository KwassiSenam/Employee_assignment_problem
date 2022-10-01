#include <vector>
#include <algorithm>
#include <cmath>

#include "individu.h"

using namespace std;

std::vector<int> tmp;
std::list<int> t;
std::list<int> liste_distances;
std::list<int> liste_des_indices;
std::vector<int> mylist;
std::vector<int> mylist2;


// initialisation des paramètres d'un individu
individu::individu()
{
	int a;
	// un individu ici est une liste composé de 'taille' gènes ,
	taille = NBR_FORMATIONS;

	// allocation dynamique du tableau 'genes'
	genes = new int[NBR_FORMATIONS];

	// création de la liste regroupant les différentes interfaces
	for (int i=0; i< NBR_INTERFACES; i++)
	{
		mylist.push_back (i);
	}

	int n=0;
	bool success = false;
	int maxN = 0;
	while (!success) {
		n = 0;
		success = true;
		while (n < taille && success)
		{
			tmp = mylist;
			// on tire aléatoirement le gène suivante
			success = false;
			if (maxN <= n) {
				maxN = n;
				// cout << maxN << endl;
			}

			while (!tmp.empty() && !success)
			{
				// on tire aléatoirement le gène suivante
				a = Random::aleatoire(tmp.size());
				genes[n]=tmp[a];
				if(is_valid(n, tmp[a]))
				{
					success = true;
					genes[n]=tmp[a];
					// std::cout << "Assigne interface " << tmp[a] << " a " << n << std::endl;
				}
				else
				{
					// std::cout << "Je ne peux pas assigner interface " << tmp[a] << " a " << n << std::endl;
					tmp.erase(tmp.begin() + a);
				}
			}
			if (!success) {
				// Empty list, chromosome could not be generated
				cout << "Le chromosome n'a pas pu être généré" << endl;
			}
			n +=1;
		}
	}
	mylist.clear();
}

// destruction de l'objet 'individu'
individu::~individu()
{
	delete [] genes;
}

bool individu::is_valid(int position, int valeur)
{
	int nbr_heures = 0;
	int nbr_heures_jour = 0;
	std::list<int> tmp_formations;
	int jour = LUNDI;

	// Même compétence
	if(Data::competences_interfaces[valeur][Data::formation[position][2]])
	{
		// Formations déjà affectés à l'interface
		for (int i=0; i <= position; i++)
		{
			if(genes[i] == valeur)
			{
				if (jour != Data::formation[i][3]) {
					jour = Data::formation[i][3];
					nbr_heures_jour = 0;
				}
				nbr_heures += Data::formation[i][5]- Data::formation[i][4];
				nbr_heures_jour += Data::formation[i][5]- Data::formation[i][4];
				if (i != position) {
					tmp_formations.push_back(i); // pour récupérer le numéro des formations déjà affectés à une interface "valeur"
				}
				if (nbr_heures_jour > 8) {
					// std::cout << ">8h" << std::endl;
					return false;
				}
			}
		}
		if(nbr_heures <= 35)
		{
			for (int c : tmp_formations)
			{
				if(Data::formation[position][3]==Data::formation[c][3]) {

					if(!(Data::formation[c][4] <= Data::formation[position][4] && Data::formation[c][5] <= Data::formation[position][4]) && !(Data::formation[c][4] >= Data::formation[position][5] && Data::formation[c][5] >= Data::formation[position][5])) {
						// std::cout << "chevauchement" << std::endl;
						return false;
					}
				}
			}
			return true;
		}
		else
		{
			// std::cout << ">35h" << std::endl;
			return false;
		}
	}
	else
	{
		// std::cout << "competence imcompat" << std::endl;
		return false;
	}
}


/* Moyenne : est calculée lors de la création d'un chromosome
 * et lors d'un Croisement
 */
double individu::moyenne()
{

	moy = 0;

	float position_interfaces[NBR_INTERFACES][2];
	for (int i = 0; i < NBR_INTERFACES; i++) {
		nbr_trajets[i] = 0;
		distance_interfaces[i] = 0;
		position_interfaces[i][0] = 0;
		position_interfaces[i][1] = 46;
	}

	float dist = 0;
	int pos_demi_journee = 0;
	for (int i = 0; i < NBR_FORMATIONS; i++) {
		if (Data::demi_journee[pos_demi_journee] <= i) {
			if (pos_demi_journee % 2 == 1) {
				// Nouvelle journee
				for (int j = 0; j < NBR_INTERFACES; j++) {
					dist = sqrt(position_interfaces[j][0] * position_interfaces[j][0] + (position_interfaces[j][1] - 46) * (position_interfaces[j][1] - 46));
					distance_interfaces[j] += dist;
					position_interfaces[j][0] = 0;
					position_interfaces[j][1] = 46;
					if (dist > 0) {
						nbr_trajets[j]++;
					}
				}
			}
			pos_demi_journee++;
		}

		dist = sqrt((position_interfaces[genes[i]][0] - Data::coord[Data::formation[i][1]][0]) * (position_interfaces[genes[i]][0] - Data::coord[Data::formation[i][1]][0]) + (position_interfaces[genes[i]][1] - Data::coord[Data::formation[i][1]][1]) * (position_interfaces[genes[i]][1] - Data::coord[Data::formation[i][1]][1]));
		distance_interfaces[genes[i]] += dist;
		if (dist > 0) {
			nbr_trajets[genes[i]]++;
		}
	}

	float sum = 0;
	float sum_trajets = 0;
	f_corr = 0;
	for (int j = 0; j < NBR_INTERFACES; j++) {
		dist = sqrt(position_interfaces[j][0] * position_interfaces[j][0] + (position_interfaces[j][1] - 46) * (position_interfaces[j][1] - 46));
		distance_interfaces[j] += dist;
		if (dist > 0) {
			nbr_trajets[j]++;
		}
		f_corr += distance_interfaces[j];
		sum_trajets += nbr_trajets[j];
		sum += distance_interfaces[j];
	}

	moy = sum / sum_trajets;

	// Ce n'est pas une distance moyenne
	f_corr = sum / NBR_FORMATIONS;

	return moy;
}

double individu::ecart_type(double m)
{
	float ecart_t =0;
	float carre = 0;
	for (int i = 0; i < NBR_INTERFACES; i++) {
		ecart_t = distance_interfaces[i] - m;
		carre += pow(ecart_t,2);
	}
	ecart_t = carre/(NBR_INTERFACES);
	ecart = sqrt(ecart_t);

	return ecart;
}

int individu::penalite()
{
	pen = 0;
	for (int i=0; i<taille; i++)
	{
		if(!Data::specialite_interfaces[genes[i]][Data::formation[i][1]-1])
		{
			pen +=1;
		}
	}

	this->pen = pen;
	return pen;
}

bool individu::mutation(void) {
	int n = 0;

	mylist.clear();
	for (int i = 0; i < NBR_INTERFACES; i++) {
		mylist.push_back(i);
	}

	bool succes = false;
	int limite = 0;
	while (!succes && limite < NBR_FORMATIONS) {
		n = Random::aleatoire(NBR_FORMATIONS);
		limite++;
		tmp = mylist;
		int ancienne_valeur = genes[n];
		tmp.erase(tmp.begin() + genes[n]);
		while (!tmp.empty() && !succes) {
			int a = Random::aleatoire(tmp.size());
			genes[n]=tmp[a];
			if(is_valid(n, tmp[a])) {
				genes[n]=tmp[a];
				succes = true;
			}
			else
			{
				tmp.erase(tmp.begin() + a);
			}
		}
		genes[n] = ancienne_valeur;
	}
	if (limite < NBR_FORMATIONS) {
		return true;
	} else {
		return false;
	}

}

// évaluation d'une solution : fonction qui calcule la fitness d'une solution
void individu::evaluer()
{
	fitness = 0;
	double aver = moyenne();
	double e_t = ecart_type(aver);
	int p = penalite();
	fitness = 0.5*(aver + e_t) + 0.5*f_corr*p;
}

// copie les genes d'un chromosome. la fitness n'est reprise
void individu::copier(individu* source)
{
	for (int i=0; i<taille; i++)
	{
		genes[i] = source->genes[i];
	}
}

// on échange les 2 lignes de la matrice
void individu::echange_2_genes(int gene1, int gene2)
{
	int inter = genes[gene1];
	genes[gene1] = genes[gene2];
	genes[gene2] = inter;
}

void individu::echange_2_genes_consecutifs()
{
	mylist2.clear();
	for (int i=0; i< NBR_FORMATIONS; i++)
	{
		mylist2.push_back (i);
	}
	int i ;
	bool rebuild = true;

	while (!mylist2.empty() && rebuild)
	{
		// on séléctionne un gène aléatoirement entre premier et l'avant dernier.
		// Rappel : Random::aleatoire(taille-1) retourne un entier aléatoire compris entre 0 et taille-2
		i = Random::aleatoire(mylist2.size()-1);
		if(is_valid(i,genes[i+1]) && is_valid(i+1, genes[i]))
		{
			rebuild = false;
			echange_2_genes(i,i+1);// on échange le gène séléctionné aléatoirement avec le gène le succédant
			cout<<"Mutation reussie"<<endl;
		}
		else
		{
			mylist2.erase(mylist2.begin() + i);
		}
	}
}

void individu::echange_2_genes_quelconques(int i, int j)
{
	if(i<taille && j< taille)
	{
		echange_2_genes(i, j);
	}
}

// affichage des paramètre d'un chromosome
void individu::afficher()
{
	int detrie[NBR_FORMATIONS] = {0};
	for (int i = 0; i < NBR_FORMATIONS; i++) {
		detrie[Data::retrier[i]] = genes[i];
	}
	cout << detrie[0];
	for (int i=1;i<taille;i++)
		cout << "-" << detrie[i];
	cout << endl;
	cout << " => fitness = " << fitness << endl;
}

bool individu::identique_ind(individu* indiv)
{
	for (int i=0; i<taille; i++)
		if (indiv->genes [i] != this->genes[i])
			return false;
	return true;
}
