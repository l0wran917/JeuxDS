#include "variables.h"
#include "affichage.h"

void animPerso(Perso* perso, int persoActuel){
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
			
		if(perso->imgActuelle < (8 * 5) || perso ->imgActuelle > ((8 - 2) * 5) + (8 * 5))
		{
			perso->imgActuelle = (8 * 5);
		}
		
		perso->imgActuelle += 1;
		
		if (perso->imgActuelle > ((8 - 2) * 5) + (8 * 5)) // 8 premiers img + 8 d'aprés
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

void affichageSols(Sol* solHaut, Sol* solBas, int* id){
	int i;
	int e;
	
	for(e=0;e<NBPLATEFORME;e++)
	{
		for(i=0;i<solHaut[e].longueur;i+=32)
		{
			// Ecran du haut
			if(solHaut[e].x + solHaut[e].longueur < 0 || solHaut[e].x > SCREEN_WIDTH)
			{
				oamSet(&oamMain, *id, solHaut[e].x+i, solHaut[e].y, 0, 1, SpriteSize_32x32, 
					SpriteColorFormat_256Color, solHaut[0].imgSol, -1, false, true, false, false, false);
			}
			else
			{
				oamSet(&oamMain, *id, solHaut[e].x+i, solHaut[e].y, 0, 1, SpriteSize_32x32, 
							SpriteColorFormat_256Color, solHaut[0].imgSol, -1, false, false, false, false, false);
			}
						
						
			// Ecran du bas
			if(solBas[e].x + solBas[e].longueur < 0 || solBas[e].x > SCREEN_WIDTH)
			{
				oamSet(&oamSub, *id, solBas[e].x+i, solBas[e].y, 0, 1, SpriteSize_32x32, 
					SpriteColorFormat_256Color, solBas[0].imgSol, -1, false, true, false, false, false);
			}
			else
			{
				oamSet(&oamSub, *id, solBas[e].x+i, solBas[e].y, 0, 1, SpriteSize_32x32, 
					SpriteColorFormat_256Color, solBas[0].imgSol, -1, false, false, false, false, false);
			}
			
			*id += 1;
		}
	}			
}

void affichagePieceHaut(Piece *pieceHaut, int* id){
	int i;
	
	for(i = 0; i < NBPIECEHAUT; i++)
	{
		if(pieceHaut[i].x + pieceHaut[i].tailleCote < 0 || pieceHaut[i].x > SCREEN_WIDTH)
		{
			oamSet(&oamMain, *id, pieceHaut[i].x, pieceHaut[i].y, 0, 2, SpriteSize_32x32, 
				SpriteColorFormat_256Color, pieceHaut[0].img[pieceHaut[i].imgActuelle / 4], -1, false, true, false, false, false);
		}	
		else
		{
			if(pieceHaut[i].visible) // Visible = 0 quand ramassé
			{
				oamSet(&oamMain, *id, pieceHaut[i].x, pieceHaut[i].y, 0, 2, SpriteSize_32x32, 
					SpriteColorFormat_256Color, pieceHaut[0].img[pieceHaut[i].imgActuelle / 5], -1, false, false, false, false, false);
					
					
				if(pieceHaut[i].rotation == 1)
				{
					pieceHaut[i].imgActuelle += 1;
					
					if(pieceHaut[i].imgActuelle > 3 * 5)
						pieceHaut[i].rotation = 2;
				}
				else if(pieceHaut[i].rotation == 2)
				{
					pieceHaut[i].imgActuelle -= 1;
					
					if(pieceHaut[i].imgActuelle <= 0)
						pieceHaut[i].rotation = 1;
				}
				
			}
			else // Si non visible
			{
				oamSet(&oamMain, *id, pieceHaut[i].x, pieceHaut[i].y, 0, 2, SpriteSize_32x32, 
					SpriteColorFormat_256Color, pieceHaut[0].img[pieceHaut[i].imgActuelle / 4], -1, false, true, false, false, false); // True = Hide
			}
		}
		
		*id += 1;
		
	}

}

int affichagePiegeBas(Piege *piegeBas, int* id){
	int i;
	
	for(i = 0; i < NBPIEGEBAS; i++)
	{
		if(piegeBas[i].x + piegeBas[i].tailleCote < 0 || piegeBas[i].x > SCREEN_WIDTH)
		{
			oamSet(&oamSub, *id, piegeBas[i].x, piegeBas[i].y, 0, 2, SpriteSize_32x32, 
				SpriteColorFormat_256Color, piegeBas[0].img[0], -1, false, true, false, false, false);
		}
		
		else
		{
			if(piegeBas[i].animation) // animation = 1 quand touché
			{						
				if(piegeBas[i].sensAnim == 1)
				{
					piegeBas[i].imgActuelle += 1;
					
					if(piegeBas[i].imgActuelle > 3 * 8)
						piegeBas[i].sensAnim = 2;
				}
				else if(piegeBas[i].sensAnim == 2)
				{
					piegeBas[i].imgActuelle -= 1;
					
					if(piegeBas[i].imgActuelle <= 0)
						return 1;
				}
				
				oamSet(&oamSub, *id, piegeBas[i].x, piegeBas[i].y, 0, 2, SpriteSize_32x32, 
					SpriteColorFormat_256Color, piegeBas[0].img[piegeBas[i].imgActuelle / 8], -1, false, false, false, false, false);
					
			}
			else
			{
				oamSet(&oamSub, *id, piegeBas[i].x, piegeBas[i].y, 0, 2, SpriteSize_32x32, 
					SpriteColorFormat_256Color, piegeBas[0].img[0], -1, false, true, false, false, false);
			}
		}
		
		*id += 1;
		
	}
	
	return 0;

}

void affichageChiffre(Chiffre* chiffreHaut, Chiffre* chiffreBas, int* nbPiece, int* nbMort, int* id){

	// Image piece ou mort
	oamSet(&oamMain, *id, chiffreHaut->x, chiffreHaut->y, 0, 3, SpriteSize_32x32, 
					SpriteColorFormat_256Color, chiffreHaut->img[10], -1, false, false, false, false, false);
					
					
	oamSet(&oamSub, *id, chiffreBas->x, chiffreBas->y, 0, 3, SpriteSize_32x32, 
		SpriteColorFormat_256Color, chiffreBas->img[10], -1, false, false, false, false, false);
					
	*id += 1;
	
	// Dizaine
	oamSet(&oamMain, *id, chiffreHaut->x + 32 - 7, chiffreHaut->y + 2, 0, 3, SpriteSize_32x32, 
					SpriteColorFormat_256Color, chiffreHaut->img[*nbPiece / 10], -1, false, false, false, false, false);
					
	oamSet(&oamSub, *id, chiffreBas->x + 32 - 7, chiffreBas->y + 2, 0, 3, SpriteSize_32x32, 
					SpriteColorFormat_256Color, chiffreBas->img[*nbMort / 10], -1, false, false, false, false, false);
					
	*id += 1;
	
	// Unité
	oamSet(&oamMain, *id, chiffreHaut->x + 32 - 7 + 13, chiffreHaut->y + 2, 0, 3, SpriteSize_32x32, 
					SpriteColorFormat_256Color, chiffreHaut->img[*nbPiece % 10], -1, false, false, false, false, false);
					
	oamSet(&oamSub, *id, chiffreBas->x + 32 - 7 + 13, chiffreBas->y + 2, 0, 3, SpriteSize_32x32, 
		SpriteColorFormat_256Color, chiffreBas->img[*nbMort % 10], -1, false, false, false, false, false);
					
	*id += 1;
}

