#include "variables.h"
#include "affichage.h"

void animPerso(Perso* perso, int persoActuel)
{
	if(perso->anim == STOP)
	{
		perso->imgActuelle = 0;
	}
	else if(perso->anim == DROITE)
	{
		perso->imgActuelle += 1;
		if (perso->imgActuelle > (8 - 1) * 5) // Les 8 premiers img (7 car commence à 0 et non 1)
		{
			perso->imgActuelle = 0;
		}
	}
	else if(perso->anim == GAUCHE)
	{
			
		if(perso->imgActuelle < (8 * 5) || perso ->imgActuelle > ((8 - 1) * 5) + (8 * 5))
		{
			perso->imgActuelle = (8 * 5);
		}
		
		perso->imgActuelle += 1;
		
		if (perso->imgActuelle > ((8 - 1) * 5) + (8 * 5)) // 8 premiers img + 8 d'aprés
		{
			perso->imgActuelle = (8 * 5);
		}
	}

	if(persoActuel == HAUT)
	{
		oamSet(&oamMain, 0, perso->x, perso->y, 0, 0, SpriteSize_32x32, 
			SpriteColorFormat_256Color, perso->imgSprite[perso->imgActuelle/5], -1, false, false, false, false, false);
	}
	else
	{
		oamSet(&oamSub, 0, perso->x, perso->y, 0, 0, SpriteSize_32x32, 
			SpriteColorFormat_256Color, perso->imgSprite[perso->imgActuelle/5], -1, false, false, false, false, false);
	}
}

void affichageSols(Sol* solHaut, Sol* solBas, int* id)
{
	int i;
	int e;
	
	for(e=0;e<NBPLATEFORME;e++)
	{
		for(i=0;i<solHaut[e].longueur;i+=32)
		{
			// Ecran du haut
			if(solHaut[e].x + solHaut[e].longueur < 0)
			{
				oamSet(&oamMain, *id, solHaut[e].x+i, solHaut[e].y, 0, 1, SpriteSize_32x32, 
					SpriteColorFormat_256Color, solHaut[e].imgSol, -1, false, true, false, false, false);

			}
			else
			{
				oamSet(&oamMain, *id, solHaut[e].x+i, solHaut[e].y, 0, 1, SpriteSize_32x32, 
							SpriteColorFormat_256Color, solHaut[e].imgSol, -1, false, false, false, false, false);
			}
						
						
			// Ecran du bas
			if(solBas[e].x + solBas[e].longueur < 0)
			{
				oamSet(&oamSub, *id, solBas[e].x+i, solBas[e].y, 0, 1, SpriteSize_32x32, 
					SpriteColorFormat_256Color, solBas[e].imgSol, -1, false, true, false, false, false);
			}
			else
			{
				oamSet(&oamSub, *id, solBas[e].x+i, solBas[e].y, 0, 1, SpriteSize_32x32, 
					SpriteColorFormat_256Color, solBas[e].imgSol, -1, false, false, false, false, false);
			}
			
			*id += 1;
		}
	}				
}

void affichagePieceHaut(Piece *pieceHaut, int* id){
	int i;
	
	for(i = 0; i < NBPIECEHAUT; i++)
	{
		if(pieceHaut[i].visible) // Visible = 0 quand ramassé
		{
			oamSet(&oamMain, *id, pieceHaut[i].x, pieceHaut[i].y, 0, 2, SpriteSize_32x32, 
				SpriteColorFormat_256Color, pieceHaut[i].img[pieceHaut[i].imgActuelle / 4], -1, false, false, false, false, false);
				
			pieceHaut[i].imgActuelle += 1;
			
			if(pieceHaut[i].imgActuelle > 6 * 4)
				pieceHaut[i].imgActuelle = 0;
				
			
		}
		else // Si non visible
		{
			oamSet(&oamMain, *id, pieceHaut[i].x, pieceHaut[i].y, 0, 2, SpriteSize_32x32, 
				SpriteColorFormat_256Color, pieceHaut[i].img[pieceHaut[i].imgActuelle / 4], -1, false, true, false, false, false); // True = Hide
		}
		
		*id += 1;
		
	}

}

int affichagePiegeBas(Piege *piegeBas, int* id){
	int i;
	
	for(i = 0; i < NBPIEGEBAS; i++)
	{
		if(piegeBas[i].animation) // animation = 1 quand touché
		{		
			piegeBas[i].imgActuelle += 1;
			
			if(piegeBas[i].imgActuelle > 7 * 6)
			{
				return 1;
			}
			
			oamSet(&oamSub, *id, piegeBas[i].x, piegeBas[i].y, 0, 2, SpriteSize_32x32, 
				SpriteColorFormat_256Color, piegeBas[0].img[piegeBas[i].imgActuelle / 6], -1, false, false, false, false, false);
				
		}
		else
		{
			oamSet(&oamSub, *id, piegeBas[i].x, piegeBas[i].y, 0, 2, SpriteSize_32x32, 
				SpriteColorFormat_256Color, piegeBas[i].img[0], -1, false, true, false, false, false);
		}
		
		*id += 1;
		
	}
	
	return 0;

}