#include "variables.h"
#include "calculs.h"

void deplacementPerso(Perso* persoHaut, Perso* persoBas, int persoActuel, int direction){
	
	if(direction == DROITE) {
		if(persoActuel == HAUT)
			persoHaut->deplacement[X] += persoHaut->vitesse;
		else
			persoBas->deplacement[X] += persoBas->vitesse;
	}
	
	if(direction == GAUCHE) {
		if(persoActuel == HAUT)
			persoHaut->deplacement[X] -= persoHaut->vitesse;
		else
			persoBas->deplacement[X] -= persoBas->vitesse;
	}
	
	if(direction == SAUT) {
		if(persoActuel == HAUT)
		{
			if (persoHaut->nbSaut < 2){
				persoHaut->acceleration[Y] -= persoHaut->hauteurSaut;
				persoHaut->nbSaut++;
			}
		}
		else
		{
			if (persoBas->nbSaut < 2){
				persoBas->acceleration[Y] = -persoBas->hauteurSaut; // On reset acceleration vers le bas et on réaugmente saut
				persoBas->nbSaut++;
			}
		}
	}
	
}

int collisionSolY(Perso* perso, Sol* plateforme){

	int e;
		
	for(e=0;e<NBPLATEFORME;e++)
	{
		if(perso->x + perso->largeur - 9 >= plateforme[e].x + 1 && perso->x + 9 <= plateforme[e].x+plateforme[e].longueur) // 9 = Vide case img 32x32
		{
			if(perso->y + perso->hauteur + perso->acceleration[Y] - 4 >= plateforme[e].y && perso->y + perso->acceleration[Y] + 2 <= plateforme[e].y + plateforme[e].hauteur)
			{		
				perso->nbSaut = 0;
				return 1;
			}
		}
	}
	
	return 0;
	
}

int collisionSolX(Perso* perso, Sol* plateforme)
{
	int e;

	for(e=0;e<NBPLATEFORME;e++)
	{ 
		if(perso->y + perso->hauteur + perso->acceleration[Y] - 6 >= plateforme[e].y && perso->y <= plateforme[e].y + plateforme[e].hauteur)
		{
			if(perso->x + perso->largeur + perso->deplacement[X] - 9 > plateforme[e].x && perso->x + perso->deplacement[X] + 9 < plateforme[e].x + plateforme[e].longueur)
			{
				return 1;
			}
		}	
	}
}

void collisionPiece(Perso* perso, Piece* piece){
	int i;
	
	for(i = 0; i < NBPIECEHAUT; i++)
	{		
		if(perso->x + perso->largeur - 9 >= piece[i].x + 10 && perso->x + 9 <= piece[i].x + 10) // 10 car il y a 10 px vide autour de la piece dans l'img
		{
			if(perso->y + (perso->hauteur / 2) >= piece[i].y && perso->y + (perso->hauteur / 2) <= piece[i].y + 32) // 32 = Hauteur img
			{	
				piece[i].visible = 0;
			}
		}
		
	}
}

void collisionPiege(Perso* perso, Piege* piege){
	int i;
	
	for(i = 0; i < NBPIEGEBAS; i++)
	{		 
		if(perso->x >= piege[i].x && perso->x + perso->largeur - 2 <= piege[i].x + piege[i].tailleCote)
		{
			if(perso->y + perso->hauteur <= piege[i].y + piege[i].tailleCote && perso->y + perso->hauteur - 6 >= piege[i].y)
			{
				piege[i].animation = 1;
				perso->deplacement[X] = 0;
				perso->acceleration[Y] = 0;
				perso->anim = 0;
			}
		}
		
	}
}

void scroll(Perso* perso, Sol* plateforme, Piece* piece, Piege* piege, int ecran){
	int i;

	if (perso->x + perso->largeur + perso->deplacement[X] > SCREEN_WIDTH - 96 || perso->x + perso->deplacement[X] < 96)
	{
		for(i = 0;i < NBPLATEFORME; i++)
		{
			plateforme[i].x -= perso->deplacement[X];
		}
		
		if(ecran == HAUT)
		{
			for(i = 0;i < NBPIECEHAUT; i++)
			{
				piece[i].x -= perso->deplacement[X];
			}
		}
		else if(ecran == BAS)
		{
			for(i = 0;i < NBPIEGEBAS; i++)
			{
				piege[i].x -= perso->deplacement[X];
			}
		}
		
		perso->deplacement[X] = 0;
	}


}