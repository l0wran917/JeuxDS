<<<<<<< HEAD
#include "variables.h"


int main(void) {
	
	// Variables
	Sol solHaut[NBPLATEFORME];
	Sol solBas[NBPLATEFORME];
	Piece pieceHaut[NBPIECEHAUT];
	Piege piegeBas[NBPIEGEBAS];
	Perso persoHaut;
	Perso persoBas;
	Chiffre chiffreHaut;
	Chiffre chiffreBas;
	int bg, bgSub;
	int persoActuel = HAUT;
	int idSprite = 1;
	int nbPiece = 0;
	int nbMort = 0;
	int etatJeu = 0;
	//
	
	
	// Init
	initAffichage(&bg, &bgSub, &persoHaut, &persoBas);
	initChiffreHaut(&chiffreHaut, (u8*)chiffreTiles);
	initChiffreBas(&chiffreBas, (u8*)chiffreTiles);
	initSol(&solHaut, (u8*)solTiles, 1, HAUT);
	initSol(&solBas, (u8*)solTiles, 1, BAS);
	initPieceHaut(&pieceHaut, (u8*)pieceTiles, 1);
	initPiegeBas(&piegeBas, (u8*)piegeTiles, 1);
	initPerso(&persoHaut, 100, 45, (u8*)persoHautTiles, 1, HAUT);
	initPerso(&persoBas, 100, 45, (u8*)persoBasTiles, 1, BAS);
	//
	
	//consoleDemoInit(); // Affichage console pour debug
	
	while(1) {		
		scanKeys(); // Analyse les touches qui sont appuyées
		
		// Changement perso
		if(keysDown() & KEY_R)
		{
			if(persoActuel == HAUT) // Si celui du haut actuellement, on prend celui du bas sinon on prends celui du haut
			{
				persoActuel = BAS;
				dmaCopy(backgroundJourBitmap, bgGetGfxPtr(bgSub), backgroundJourBitmapLen);
				dmaCopy(backgroundNuitBitmap, bgGetGfxPtr(bg), backgroundNuitBitmapLen);
			}
			else
			{
				persoActuel = HAUT;
				dmaCopy(backgroundJourBitmap, bgGetGfxPtr(bg), backgroundJourBitmapLen);
				dmaCopy(backgroundNuitBitmap, bgGetGfxPtr(bgSub), backgroundNuitBitmapLen);
			}
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
			if(etatJeu != 3) // Si jeu n'est pas gagné
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
		collisionPiece(&persoHaut, &pieceHaut, &nbPiece);
		//
		
		// Test collision piege
		collisionPiege(&persoBas, &piegeBas);
		//
		
		// Chute du perso
		if (chutePerso (&persoHaut, &persoBas) == 1) // Perso du Haut
		{
			initSol(&solHaut, (u8*)solTiles, 0, HAUT);
			initPieceHaut(&pieceHaut, (u8*)pieceTiles, 0);
			initPerso(&persoHaut, 100, 45, (u8*)persoHautTiles, 0, HAUT);
			nbMort++;
		}
		if (chutePerso (&persoHaut, &persoBas) == 2) // Perso du Bas
		{
			initSol(&solBas, (u8*)solTiles, 0, BAS);
			initPiegeBas(&piegeBas, (u8*)piegeTiles, 0);
			initPerso(&persoBas, 100, 45, (u8*)persoBasTiles, 0, BAS);
			nbMort++;
		}
		
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
		
		// Verifie etat jeu
		etatJeu = fin(&persoHaut, &persoBas, persoActuel, &bg, &bgSub, &nbPiece, &solHaut, &solBas);
		if(etatJeu == 3)
		{
			persoHaut.deplacement[X] = 0.0;
			
			persoBas.deplacement[X] = 0.0;
			
			persoHaut.imgActuelle = 0;
			persoBas.imgActuelle = 0;
		}
		//
		
		// Applique deplacement au perso
		persoHaut.x += persoHaut.deplacement[X];
		persoHaut.y += persoHaut.deplacement[Y];
		
		persoBas.x += persoBas.deplacement[X];
		persoBas.y += persoBas.deplacement[Y];
		//
		
		// Affichage
		if(etatJeu == 0)
		{
			if(persoActuel == HAUT) // Si celui du haut actuellement, on prend celui du bas sinon on prends celui du haut
			{
				dmaCopy(backgroundJourDebutHautBitmap, bgGetGfxPtr(bg), backgroundJourDebutHautBitmapLen);
				dmaCopy(backgroundNuitDebutBasBitmap, bgGetGfxPtr(bgSub), backgroundNuitDebutBasBitmapLen);
			}
			else
			{
				dmaCopy(backgroundJourDebutBasBitmap, bgGetGfxPtr(bgSub), backgroundJourDebutBasBitmapLen);
				dmaCopy(backgroundNuitDebutHautBitmap, bgGetGfxPtr(bg), backgroundNuitDebutHautBitmapLen);
			}
		}
		else if(etatJeu == 1)
		{
			if(persoActuel == HAUT) // Si celui du haut actuellement, on prend celui du bas sinon on prends celui du haut
			{
				dmaCopy(backgroundJourBitmap, bgGetGfxPtr(bg), backgroundJourBitmapLen);
				dmaCopy(backgroundNuitBitmap, bgGetGfxPtr(bgSub), backgroundNuitBitmapLen);
			}
			else
			{
				dmaCopy(backgroundJourBitmap, bgGetGfxPtr(bgSub), backgroundJourBitmapLen);
				dmaCopy(backgroundNuitBitmap, bgGetGfxPtr(bg), backgroundNuitBitmapLen);
			}
		}
		else if(etatJeu == 2)
		{
			if(persoActuel == HAUT) // Si celui du haut actuellement, on prend celui du bas sinon on prends celui du haut
			{
				dmaCopy(backgroundJourPieceBitmap, bgGetGfxPtr(bg), backgroundJourPieceBitmapLen);
				dmaCopy(backgroundNuitBitmap, bgGetGfxPtr(bgSub), backgroundNuitBitmapLen);
			}
			else
			{
				dmaCopy(backgroundJourBitmap, bgGetGfxPtr(bgSub), backgroundJourBitmapLen);
				dmaCopy(backgroundNuitPieceBitmap, bgGetGfxPtr(bg), backgroundNuitPieceBitmapLen);
			}
		}
		else if(etatJeu == 3)
		{
			if(persoActuel == HAUT) // Si celui du haut actuellement, on prend celui du bas sinon on prends celui du haut
			{
				dmaCopy(backgroundJourGagneBitmap, bgGetGfxPtr(bg), backgroundJourGagneBitmapLen);
				dmaCopy(backgroundNuitGagneBitmap, bgGetGfxPtr(bgSub), backgroundJourGagneBitmapLen);
			}
			else
			{
				dmaCopy(backgroundJourGagneBitmap, bgGetGfxPtr(bgSub), backgroundJourGagneBitmapLen);
				dmaCopy(backgroundNuitGagneBitmap, bgGetGfxPtr(bg), backgroundNuitGagneBitmapLen);
			}
		}
		affichageSols(&solHaut, &solBas, &idSprite);
		affichagePieceHaut(&pieceHaut, &idSprite);
		animPerso(&persoHaut, HAUT);
		animPerso(&persoBas, BAS);
		if(affichagePiegeBas(&piegeBas, &idSprite) == 1)
		{
			initSol(&solBas, (u8*)solTiles, 0, BAS);
			initPiegeBas(&piegeBas, (u8*)piegeTiles, 0);
			initPerso(&persoBas, 100, 45, (u8*)persoBasTiles, 0, BAS);
			nbMort++;
		}
		affichageChiffre(&chiffreHaut, &chiffreBas, &nbPiece, &nbMort, &idSprite, &nbPiece);	
		//
		
		// Reinitialise deplacement
		persoHaut.deplacement[X] = 0;
		persoHaut.deplacement[Y] = 0;
		
		persoBas.deplacement[X] = 0;
		persoBas.deplacement[Y] = 0;
		//
				
		idSprite = 1;
		
		// Applique les modifs
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		// Reset les sprites
		oamClear(&oamMain, 0, 0);
		oamClear(&oamSub, 0, 0);
		// Attends pour cadence de 60 FPS (= IPS)
		swiWaitForVBlank();
		
		
	}
	return 0;
=======
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
>>>>>>> 09bf57a2209d2f8718808e1f34adc55117b2738a
}