#include <iostream>
#include "data.h"
#include <vector>

using namespace std;
std::vector<int> jours;

int main(int argc, char **argv)
{
    cout<<"Hello world" <<endl;
    /* Trier en ordre croissant les jours de formations par la méthode de tri bulle*/
    bool permut;
    int tampon[6];
	do
	{
	    permut=false;
        for(int i=0;i<NBR_FORMATIONS-1;i++)
        {
            if(formation[i][3] > formation[i+1][3])
            {
                for(int j=0; j<6; j++)  //copie de toute la ligne
                {
                    tampon[j]=formation[i][3];
                }
                for(int j=0; j<6; j++)
                {
                    formation[i][j]=formation[i+1][j];      //affectation de toute la ligne
                }
                for(int j=0; j<6; j++)
                {
                    formation[i+1][j]=tampon[j];
                }
                permut=true;
            }
	   }
	}while (permut==true);
    /*Fin tri Bulle*/

    //affichage jours
    for(int i=0;i<NBR_FORMATIONS;i++)
    {
        cout <<formation[i][3] <<endl;;
    }

    /* Trier en ordre croissant les heures de formations par la méthode de tri bulle
    bool permut_bis;
	do
	{
	    permut_bis=false;
        for(int i=0;i<NBR_FORMATIONS-1;i++)
        {
            if(formation[i][4] > formation[i+1][4])
            {
                int tampon=formation[i][4];
                formation[i][4]=formation[i+1][4];
                formation[i+1][4]=tampon;
                permut_bis=true;
            }
	   }
	}while (permut_bis==true);

    //affichage heures
    for(int i=0;i<NBR_FORMATIONS;i++)
    {
        cout <<formation[i][4] <<endl;;
    }

*/
}
