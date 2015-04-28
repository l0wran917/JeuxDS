#include "variables.h"
#include "initialisation.h"


void initAffichage(int* bg, int* bgSub, Perso* persoHaut, Perso* persoBas){
	// Initialise le mode affiche
	videoSetMode(MODE_5_2D); // MODE_5_2D : Mode permet afficher + de chose
	videoSetModeSub(MODE_5_2D);
	
	// Prepare la memoire (dit à la mémoire ce qu'on va mettre dedans)
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
	dmaCopy(backgroundJourBitmap, bgGetGfxPtr(*bg), backgroundJourBitmapLen);
	dmaCopy(backgroundNuitBitmap, bgGetGfxPtr(*bgSub), backgroundNuitBitmapLen);
	
	// initialise la memoire pour les sprites
	oamInit(&oamMain, SpriteMapping_1D_32, true);
	oamInit(&oamSub, SpriteMapping_1D_32, true);

	// Copie les palettes des sprites haut dans la memoire
	dmaCopy(persoHautPal, VRAM_F_EXT_SPR_PALETTE[0], 256);
	dmaCopy(solPal, VRAM_F_EXT_SPR_PALETTE[1], 256);
	dmaCopy(piecePal, VRAM_F_EXT_SPR_PALETTE[2], 256);
	dmaCopy(chiffrePal, VRAM_F_EXT_SPR_PALETTE[3], 256);
	
	// Copie les palettes dans sprites bas dans la memoire
	dmaCopy(persoBasPal, VRAM_I_EXT_SPR_PALETTE[0], 256);
	dmaCopy(solPal, VRAM_I_EXT_SPR_PALETTE[1], 256);
	dmaCopy(piegePal, VRAM_I_EXT_SPR_PALETTE[2], 256);
	dmaCopy(chiffrePal, VRAM_I_EXT_SPR_PALETTE[3], 256);
	
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE); // On doit ecrire dedans avant de la former en tant que palette_ext
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE); // On doit ecrire dedans avant de la former en tant que palette_ext
}

void initSol(Sol* sol, u8* img, int initImg, int ecran){
	
	if(initImg)
	{
		if(ecran == HAUT)
		{
			sol[0].imgSol = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
			dmaCopy(img, sol[0].imgSol, 32*32);
		}
		else
		{
			sol[0].imgSol = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
			dmaCopy(img, sol[0].imgSol, 32*32);
		}
	}
{	// Init coord sol
	sol[0].x = 0;
	sol[0].y = 192 - 20;
	sol[0].longueur = SCREEN_WIDTH - 32;
	sol[0].hauteur = 20;
	
	sol[1].x = SCREEN_WIDTH - 32;
	sol[1].y = 192 - 20;
	sol[1].longueur = 32 * 5;
	sol[1].hauteur = 20;
	
	sol[2].x = SCREEN_WIDTH - 32;
	sol[2].y = 192 - 40;
	sol[2].longueur = 32 * 5;
	sol[2].hauteur = 20;

	sol[3].x = SCREEN_WIDTH;
	sol[3].y = 192 - 60;
	sol[3].longueur = 32 * 4;
	sol[3].hauteur = 20;
	
	sol[4].x = SCREEN_WIDTH + 32;
	sol[4].y = 192 - 80;
	sol[4].longueur = 32 * 3;
	sol[4].hauteur = 20;
	
	sol[5].x = SCREEN_WIDTH + 32 * 2;
	sol[5].y = 192 - 100;
	sol[5].longueur = 32 * 2;
	sol[5].hauteur = 20;
	
	sol[6].x = SCREEN_WIDTH + 32 * 5;
	sol[6].y = 192 - 100;
	sol[6].longueur = 32;
	sol[6].hauteur = 20;
	
	sol[7].x = SCREEN_WIDTH + 32 * 7;
	sol[7].y = 192 - 100 - 40;
	sol[7].longueur = 32;
	sol[7].hauteur = 20;
	
	sol[8].x = SCREEN_WIDTH + 32 * 7;
	sol[8].y = 192 - 100 + 32;
	sol[8].longueur = 32;
	sol[8].hauteur = 20;
	
	sol[9].x = 2 * SCREEN_WIDTH + 32;
	sol[9].y = 192 - 100;
	sol[9].longueur = 32;
	sol[9].hauteur = 20;
	
	sol[10].x = 2 * SCREEN_WIDTH + 32 * 3;
	sol[10].y = 192 - 100 - 40;
	sol[10].longueur = 32;
	sol[10].hauteur = 20;
	
	sol[11].x = 2 * SCREEN_WIDTH + 32 * 3;
	sol[11].y = 192 - 100 + 32;
	sol[11].longueur = 32;
	sol[11].hauteur = 20;
	
	sol[12].x = 2 * SCREEN_WIDTH + 32 * 5;
	sol[12].y = 192 - 20;
	sol[12].longueur = 32 * 5;
	sol[12].hauteur = 20;
	
	sol[13].x = 2 * SCREEN_WIDTH + 32 * 5;
	sol[13].y = 192 - 40;
	sol[13].longueur = 32 * 5;
	sol[13].hauteur = 20;
	
	sol[14].x = 2 * SCREEN_WIDTH + 32 * 5;
	sol[14].y = 192 - 60;
	sol[14].longueur = 32 * 4;
	sol[14].hauteur = 20;
	
	sol[15].x = 2 * SCREEN_WIDTH + 32 * 5;
	sol[15].y = 192 - 80;
	sol[15].longueur = 32 * 3;
	sol[15].hauteur = 20;

	sol[16].x = 2 * SCREEN_WIDTH + 32 * 5;
	sol[16].y = 192 - 100;
	sol[16].longueur = 32 * 2;
	sol[16].hauteur = 20;

	sol[17].x = 3 * SCREEN_WIDTH + 32 * 2;
	sol[17].y = 192 - 20;
	sol[17].longueur = 32 * 4;
	sol[17].hauteur = 20;
	
	sol[18].x = 3 * SCREEN_WIDTH + 32 * 7;
	sol[18].y = 192 - 20;
	sol[18].longueur = 32 * 2;
	sol[18].hauteur = 20;
	
	sol[19].x = 4 * SCREEN_WIDTH + 32 * 2;
	sol[19].y = 192 - 20;
	sol[19].longueur = 32 * 6;
	sol[19].hauteur = 20;
	
	sol[20].x = 5 * SCREEN_WIDTH;
	sol[20].y = 192 - 20;
	sol[20].longueur = SCREEN_WIDTH;
	sol[20].hauteur = 20;
	
	sol[21].x = 5 * SCREEN_WIDTH + 32 * 4;
	sol[21].y = 192 - 40;
	sol[21].longueur = 32 * 4;
	sol[21].hauteur = 20;
	
	sol[22].x = 5 * SCREEN_WIDTH + 32 * 6;
	sol[22].y = 192 - 60;
	sol[22].longueur = 32 * 2;
	sol[22].hauteur = 20;
	
	sol[23].x = -32;
	sol[23].y = 0;
	sol[23].longueur = 32;
	sol[23].hauteur = SCREEN_HEIGHT;
	
	sol[24].x = 6 * SCREEN_WIDTH;
	sol[24].y = 0;
	sol[24].longueur = 32;
	sol[24].hauteur = SCREEN_HEIGHT;
}
}

void initPerso(Perso* perso, int x, int y, u8* img, int initImg, int ecran){
	int i;

	perso->x = x;
	perso->y = y;
	
	perso->vitesse = 1.2;
	perso->hauteurSaut = 2.5;
	
	perso->hauteur = 32;
	perso->largeur = 32;

	perso->nbSaut = 0;
	
	perso->imgActuelle = 0;
	
	perso->acceleration[X] = 0;
	perso->acceleration[Y] = 0;
	
	perso->deplacement[X] = 0;
	perso->deplacement[Y] = 0;
	
	if(initImg)
	{
		for(i=0;i<16;i++)
		{
			if(ecran == HAUT)
			{
				// Donne moi un endroit ou stocker mon sprite
				perso->imgSprite[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
			}
			else
			{
				perso->imgSprite[i] = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
			}
			
			// Copie l'img de 32*32 dans la case du tableau
			dmaCopy(img, perso->imgSprite[i], 32*32);
			
			// Avance de 32*32 octets (?) dans l'img
			img += 32*32;
		}
	}
}

void initPieceHaut(Piece* pieceHaut, u8* img, int initImg){
	int i = 0, e = 0;

	pieceHaut[0].x = 32 * 5;
	pieceHaut[0].y = 145;
	
	pieceHaut[1].x = SCREEN_WIDTH;
	pieceHaut[1].y = 145 - 40;
	
	pieceHaut[2].x = SCREEN_WIDTH + 32 * 2;
	pieceHaut[2].y = 145 - 80;
	
	pieceHaut[3].x = SCREEN_WIDTH + 32 * 7;
	pieceHaut[3].y = 145 - 80 - 40;
	
	pieceHaut[4].x = 2 * SCREEN_WIDTH + 32 * 3;
	pieceHaut[4].y = 145 - 80 + 32;
	
	pieceHaut[5].x = 2 * SCREEN_WIDTH + 32 * 7;
	pieceHaut[5].y = 145 - 60;
	
	pieceHaut[6].x = 3 * SCREEN_WIDTH + 32;
	pieceHaut[6].y = 145 - 20;
	
	pieceHaut[7].x = 3 * SCREEN_WIDTH + 32 * 7;
	pieceHaut[7].y = 145;
	
	pieceHaut[8].x = 4 * SCREEN_WIDTH + 32 * 4 - 16;
	pieceHaut[8].y = 145;
	
	pieceHaut[9].x = 4 * SCREEN_WIDTH + 32 * 7 - 16;
	pieceHaut[9].y = 145;
	
	pieceHaut[10].x = 5 * SCREEN_WIDTH + 32 * 2 - 16;
	pieceHaut[10].y = 145;
	
	pieceHaut[11].x = 5 * SCREEN_WIDTH + 32 * 5;
	pieceHaut[11].y = 145 - 20;
	
		
	if(initImg)
	{
		for(i = 0; i < NBPIECEHAUT ; i++) // On a NBPIECEHAUT pieces à initialiser
		{		
			pieceHaut[i].tailleCote = 32;
			pieceHaut[i].imgActuelle = 0;
			pieceHaut[i].rotation = 1;
			pieceHaut[i].visible = 1;
		}
		
		for(e = 0; e < 5; e++) // On a 6 img pour piece
		{
			// Donne moi un endroit ou stocker mon sprite
			pieceHaut[0].img[e] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
			
			// Copie l'img de 32*32 dans la case du tableau
			dmaCopy(img, pieceHaut[0].img[e], 32*32);
			
			// Avance de 32*32 octets (?) dans la memoire qui contient l'image
			img += 32*32;
		}
	}
	
}

void initPiegeBas(Piege* piegeBas, u8* img, int initImg){
	int i = 0, e = 0;

	piegeBas[0].x = 32 * 5;
	piegeBas[0].y = 145;
	
	piegeBas[1].x = SCREEN_WIDTH;
	piegeBas[1].y = 145 - 40;
	
	piegeBas[2].x = SCREEN_WIDTH + 32 * 2;
	piegeBas[2].y = 145 - 80;
	
	piegeBas[3].x = SCREEN_WIDTH + 32 * 7;
	piegeBas[3].y = 145 - 80 - 40;
	
	piegeBas[4].x = 2 * SCREEN_WIDTH + 32 * 3;
	piegeBas[4].y = 145 - 80 + 32;
	
	piegeBas[5].x = 2 * SCREEN_WIDTH + 32 * 7;
	piegeBas[5].y = 145 - 60;
	
	piegeBas[6].x = 3 * SCREEN_WIDTH + 32;
	piegeBas[6].y = 145 - 20;
	
	piegeBas[7].x = 3 * SCREEN_WIDTH + 32 * 7;
	piegeBas[7].y = 145;
	
	piegeBas[8].x = 4 * SCREEN_WIDTH + 32 * 4 - 16;
	piegeBas[8].y = 145;
	
	piegeBas[9].x = 4 * SCREEN_WIDTH + 32 * 7 - 16;
	piegeBas[9].y = 145;
	
	piegeBas[10].x = 5 * SCREEN_WIDTH + 32 * 2 - 16;
	piegeBas[10].y = 145;
	
	piegeBas[11].x = 5 * SCREEN_WIDTH + 32 * 5;
	piegeBas[11].y = 145 - 20;
		
	if(initImg)
	{
		for(e = 0; e < 5; e++) // On a 9 img pour piece
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
		piegeBas[i].sensAnim = 1;
	}
	
}

void initChiffreHaut(Chiffre* chiffre, u8* img){
	int i;
	
	chiffre->x = 0;
	chiffre->y = 0;
	
	for(i = 0; i < 10; i++)
	{
		chiffre->img[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		
		dmaCopy(img, chiffre->img[i], 32*32);
		
		img += 32*32;
	}
	
	chiffre->img[10] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	dmaCopy(img, chiffre->img[10], 32*32);
}

void initChiffreBas(Chiffre* chiffre, u8* img){
	int i;
	
	chiffre->x = 5;
	chiffre->y = 5;
	
	for(i = 0; i < 10; i++)
	{
		chiffre->img[i] = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
		
		dmaCopy(img, chiffre->img[i], 32*32);
		
		img += 32*32;
	}
	
	img += 32*32;
	
	chiffre->img[10] = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
	dmaCopy(img, chiffre->img[10], 32*32);
}