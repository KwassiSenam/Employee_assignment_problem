#ifndef DATA_H
#define DATA_H

#include <list>
#include <algorithm>

#define NBR_INTERFACES        16
#define NBR_INTERFACES_TOTAL  16
#define NBR_APPRENANTS        20
#define NBR_FORMATIONS_PAR_SEMAINE 4
#define NBR_FORMATIONS        NBR_APPRENANTS * NBR_FORMATIONS_PAR_SEMAINE
#define NBR_FORMATIONS_TOTAL  80
#define NBR_CENTRES_FORMATION 5
#define NBR_SPECIALITES       5
#define NBR_NODES 	      NBR_CENTRES_FORMATION+1

/* code des compétence en langage des signes et en codage LPC */
#define COMPETENCE_SIGNES     0
#define COMPETENCE_CODAGE     1


#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6

/* spécialités des interfaces */
#define SPECIALITE_MENUISERIE 1
#define SPECIALITE_ELECTRICITE 2
#define SPECIALITE_MECANIQUE 3
#define SPECIALITE_INFORMATIQUE 4
#define SPECIALITE_CUISINE 5



class Data{
	public:
		// ATTRIBUTS
		static int formation[NBR_FORMATIONS_TOTAL][6];
		static int competences_interfaces[NBR_INTERFACES_TOTAL][2];
		static float coord[NBR_NODES][2];
		static int specialite_interfaces[NBR_INTERFACES_TOTAL][NBR_SPECIALITES];

		static int retrier[NBR_FORMATIONS];

		static int demi_journee[11];

		// METHODS
		static void tri_formations(void) {
			/* Trier en ordre croissant les jours de formations par la méthode de tri bulle*/
			int tampon[6];
			bool permut;

			int tampon_tri;
			for (int i = 0; i < NBR_FORMATIONS; i++) {
				retrier[i] = i;
			}

			do
			{
				permut=false;
				for(int i=0;i<NBR_FORMATIONS-1;i++)
				{
					if(formation[i][3] > formation[i+1][3] || (formation[i][3] == formation[i+1][3] && formation[i][4] > formation[i+1][4]))
					{
						for(int j=0; j<6; j++)  //copie de toute la ligne
						{
							tampon[j]=formation[i][j];
						}
						for(int j=0; j<6; j++)
						{
							formation[i][j]=formation[i+1][j];      //affectation de toute la ligne
						}
						for(int j=0; j<6; j++)
						{
							formation[i+1][j]=tampon[j];
						}
						tampon_tri = retrier[i];
						retrier[i] = retrier[i+1];
						retrier[i+1] = tampon_tri;

						permut=true;
					}
				}
			}while (permut==true);

            // tri par demi-journée
			int jour = LUNDI;
			int index = 0;
			bool matin = true;
			for (int i = 0; i < 11; i++) {
				while (formation[index][3] == jour && (!matin || (matin && formation[index][4] <= 12))) {
					index++;
				}
				demi_journee[i] = index;
				if (!matin) {
					jour++;
				}
				matin = !matin;
			}
		}

};

# endif



