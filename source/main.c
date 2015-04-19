#include "variables.h"

#include "backgroundHaut.h"
#include "backgroundBas.h"
#include "persoHaut.h"
#include "persoBas.h"
#include "piece.h"
#include "piege.h"
#include "sol.h"

int main(void) {
	
	// Variables
	Sol solHaut[NBPLATEFORME];
	Sol solBas[NBPLATEFORME];
	Perso persoHaut;
	Perso persoBas;
	Piece pieceHaut[NBPIECEHAUT];
	Piege piegeBas[NBPIEGEBAS];
	int bg, bgSub;
	int persoActuel = HAUT;
	int idSprite = 1;
	//
	
	
	// Init
	initAffichage(&bg, &bgSub, &persoHaut, &persoBas);
	initSol(&solHaut, &solBas, (u8*)solTiles, 1);
	initPieceHaut(&pieceHaut, (u8*)pieceTiles);
	initPiegeBas(&piegeBas, (u8*)piegeTiles);
	initPerso(&persoHaut, 100, 45);
	initPerso(&persoBas, 100, 45);
	//		
	
	while(1) {		
		scanKeys();		
		
		// Changement perso
		if(keysDown() & KEY_R)
		{
			if(persoActuel == HAUT) // Si celui du haut actuellement, on prend celui du bas sinon on prends celui du haut
				persoActuel = BAS;
			else
				persoActuel = HAUT;
		}
		
		persoHaut.anim = STOP;
		persoBas.anim = STOP;
		
		if(keysHeld() & KEY_RIGHT)
		{
			deplacementPerso(&persoHaut, &persoBas, persoActuel, DROITE);
			
			if(persoActuel == HAUT)
				persoHaut.anim = DROITE;
			else
				persoBas.anim = DROITE;
		}
	 
		if(keysHeld() & KEY_LEFT)
		{
			deplacementPerso(&persoHaut, &persoBas, persoActuel, GAUCHE);
			
			if(persoActuel == HAUT)
				persoHaut.anim = GAUCHE;
			else
				persoBas.anim = GAUCHE;
		}
		
		if(keysDown() & KEY_A)
		{
			deplacementPerso(&persoHaut, &persoBas, persoActuel, SAUT);	
		}		

		// Gravité
		persoHaut.acceleration[Y] += 0.1;
		persoBas.acceleration[Y] += 0.1;
		//
		
		// Test Collision avec sol, si collision on supprime acceleration gravité
		if(collisionSolY(&persoHaut, &solHaut) == 1)
			persoHaut.acceleration[Y] = 0;
			
		if(collisionSolY(&persoBas, &solBas) == 1)
			persoBas.acceleration[Y] = 0;
			
		if(collisionSolX(&persoHaut, &solHaut) == 1)
			persoHaut.deplacement[X] = 0;
			
		if(collisionSolX(&persoBas, &solBas) == 1)
			persoBas.deplacement[X] = 0;

		//
		
		// Test collision piece
		collisionPiece(&persoHaut, &pieceHaut);
		//
		
		// Test collision piege
		collisionPiege(&persoBas, &piegeBas);
		//
		
		// Scroll
		scroll(&persoHaut, &solHaut, &pieceHaut, &piegeBas, HAUT);
		scroll(&persoBas, &solBas, &pieceHaut, &piegeBas, BAS);
		//
		
		// Applique acceleration au deplacement
		persoHaut.deplacement[X] += persoHaut.acceleration[X];
		persoHaut.deplacement[Y] += persoHaut.acceleration[Y];
		
		persoBas.deplacement[X] += persoBas.acceleration[X];
		persoBas.deplacement[Y] += persoBas.acceleration[Y];
		//
		
		// Applique deplacement au perso
		persoHaut.x += persoHaut.deplacement[X];
		persoHaut.y += persoHaut.deplacement[Y];
		
		persoBas.x += persoBas.deplacement[X];
		persoBas.y += persoBas.deplacement[Y];
		//
		
		// Affichage
		affichageSols(&solHaut, &solBas, &idSprite);
		affichagePieceHaut(&pieceHaut, &idSprite);
		animPerso(&persoHaut, HAUT);
		animPerso(&persoBas, BAS);
		if(affichagePiegeBas(&piegeBas, &idSprite) == 1)
		{
			initSol(&solHaut, &solBas, (u8*)solTiles, 0);
			initPiegeBas(&piegeBas, (u8*)piegeTiles, 0);
			initPerso(&persoBas, 100, 45);
		}
		//
		
		// Reinitialise deplacement
		persoHaut.deplacement[X] = 0.0;
		persoHaut.deplacement[Y] = 0.0;
		
		persoBas.deplacement[X] = 0.0;
		persoBas.deplacement[Y] = 0.0;
		//
		
		idSprite = 1;
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		swiWaitForVBlank();
		
		
	}
	return 0;
}