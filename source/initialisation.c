#include "variables.h"

#include "backgroundHaut.h"
#include "backgroundBas.h"
#include "persoHaut.h"
#include "persoBas.h"
#include "piece.h"
#include "piege.h"
#include "sol.h"

#include "initialisation.h"


void initAffichage(int* bg, int* bgSub, Perso* persoHaut, Perso* persoBas){
	// Initialise le mode affiche
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);
	
	// Prepare la memoire
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankB(VRAM_B_MAIN_SPRITE);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	vramSetBankF(VRAM_F_LCD);
	vramSetBankI(VRAM_I_LCD);
	
	// Initialise le background
	*bg = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	*bgSub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	
	// Copie les données background dans l'affichage
	dmaCopy(backgroundHautBitmap, bgGetGfxPtr(*bg), backgroundHautBitmapLen);
	dmaCopy(backgroundBasBitmap, bgGetGfxPtr(*bgSub), backgroundBasBitmapLen);
	
	// initialise la memoire pour les sprites
	oamInit(&oamMain, SpriteMapping_1D_32, true);
	oamInit(&oamSub, SpriteMapping_1D_32, true);
	
	// Init sprites haut
	initSprite(persoHaut->imgSprite, persoBas->imgSprite, (u8*)persoHautTiles, (u8*)persoBasTiles);

	// Copie les palettes des sprites haut dans la memoire
	dmaCopy(persoHautPal, VRAM_F_EXT_SPR_PALETTE[0], 256);
	dmaCopy(solPal, VRAM_F_EXT_SPR_PALETTE[1], 256);
	dmaCopy(piecePal, VRAM_F_EXT_SPR_PALETTE[2], 256);
	
	// Copie les palettes dans sprites bas dans la memoire
	dmaCopy(persoBasPal, VRAM_I_EXT_SPR_PALETTE[0], 256);
	dmaCopy(solPal, VRAM_I_EXT_SPR_PALETTE[1], 256);
	dmaCopy(piegePal, VRAM_I_EXT_SPR_PALETTE[2], 256);
	
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE); // On doit ecrire dedans avant de la former en tant que palette_ext
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE); // On doit ecrire dedans avant de la former en tant que palette_ext
}


void initSprite(u16* persoHaut[], u16* persoBas[], u8* imgHaut, u8* imgBas)
{
	int i;
	
	for(i=0;i<16;i++)
	{
		// Donne moi un endroit ou stocker mon sprite
		persoHaut[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		persoBas[i] = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
		
		// Copie l'img de 32*32 dans la case du tableau
		dmaCopy(imgHaut, persoHaut[i], 32*32);
		dmaCopy(imgBas, persoBas[i], 32*32);
		
		// Avance de 32*32 octets (?) dans l'img
		imgHaut += 32*32;
		imgBas += 32*32;
	}
	
}

void initSol(Sol* solHaut, Sol* solBas, u8* img, int initImg){
	int i;

	solHaut[0].x = 30;
	solHaut[0].y = 192 - 20;
	solHaut[0].longueur = SCREEN_WIDTH;
	solHaut[0].hauteur = 20;
	if(initImg)
	{
		solHaut[0].imgSol = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(img, solHaut[0].imgSol, 32*32);
	}
	
	solHaut[1].x = SCREEN_WIDTH + 10;
	solHaut[1].y = 192 - 40;
	solHaut[1].longueur = SCREEN_WIDTH;
	solHaut[1].hauteur = 20;
	if(initImg)
	{
		solHaut[1].imgSol = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(img, solHaut[1].imgSol, 32*32);
	}
	
	solHaut[2].x = 75;
	solHaut[2].y = 192 - 100;
	solHaut[2].longueur = SCREEN_WIDTH/2;
	solHaut[2].hauteur = 20;
	if(initImg)
	{
		solHaut[2].imgSol = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(img, solHaut[2].imgSol, 32*32);
	}
	
	for(i = 0; i < NBPLATEFORME; i++)
	{
		solBas[i].x = solHaut[i].x;
		solBas[i].y = solHaut[i].y;
		solBas[i].longueur = solHaut[i].longueur;
		solBas[i].hauteur = solHaut[i].hauteur;
		if(initImg)
		{
			solBas[i].imgSol = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
			dmaCopy(img, solBas[i].imgSol, 32*32);
		}
	}
	
}

void initPerso(Perso* perso, int x, int y){
	perso->x = x;
	perso->y = y;
	
	perso->vitesse = 1.2;
	perso->hauteurSaut = 2.5;
	
	perso->hauteur = 32;
	perso->largeur = 32;

	perso->nbSaut = 0;
	
	perso->imgActuelle = 0;
}

void initPieceHaut(Piece* pieceHaut, u8* img)
{
	int i = 0, e = 0;

	pieceHaut[0].x = 115;
	pieceHaut[0].y = 145;
	
	pieceHaut[1].x = 160;
	pieceHaut[1].y = 145;
		
	
	for(i = 0; i < NBPIECEHAUT ; i++) // On a NBPIECEHAUT pieces à initialiser
	{
		for(e = 0; e < 6; e++) // On a 6 img pour piece
		{
			// Donne moi un endroit ou stocker mon sprite
			pieceHaut[i].img[e] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
			
			// Copie l'img de 32*32 dans la case du tableau
			dmaCopy(img, pieceHaut[i].img[e], 32*32);
			
			// Avance de 32*32 octets (?) dans la memoire qui contient l'image
			img += 32*32;
		}
		
		img -= 32*32 * 6; // Retour au debut de l'image

		pieceHaut[i].tailleCote = 32;
		pieceHaut[i].imgActuelle = 0;
		pieceHaut[i].visible = 1;
	}
	
}

void initPiegeBas(Piege* piegeBas, u8* img, int initImg)
{
	int i = 0, e = 0;

	piegeBas[0].x = 160;
	piegeBas[0].y = 145;
	
	piegeBas[1].x = 100;
	piegeBas[1].y = 145;
		
	if(initImg)
	{
		for(e = 0; e < 9; e++) // On a 9 img pour piece
		{
			// Donne moi un endroit ou stocker mon sprite
			piegeBas[0].img[e] = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
			
			// Copie l'img de 32*32 dans la case du tableau
			dmaCopy(img, piegeBas[0].img[e], 32*32);
			 
			// Avance de 32*32 octets (?) dans la memoire qui contient l'image
			img += 32*32;
		}
	}
	
	for(i = 0; i < NBPIEGEBAS ; i++) // On a NBPIEGEBAS pieces à initialiser
	{
		piegeBas[i].tailleCote = 32;
		piegeBas[i].imgActuelle = 0;
		piegeBas[i].animation = 0;
	}
	
}