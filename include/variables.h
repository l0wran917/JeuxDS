#include <nds.h>
#include <stdio.h>

#define NBPLATEFORME 3
#define NBPIECEHAUT 2
#define NBPIEGEBAS 2

	typedef struct Perso Perso;
	struct Perso{
		float x;
		float y;
		
		float vitesse;
		float hauteurSaut;
		
		float hauteur;
		float largeur;
		
		float deplacement[2];
		float acceleration[2];
		
		int nbSaut;
		
		int anim;
		
		int imgActuelle;
		u16* imgSprite[16];
	};
	
	typedef struct Sol Sol;
	struct	Sol{
		float x;
		float y;
		
		int hauteur;
		int longueur;
		u16* imgSol;
	};
	
	typedef struct Piece Piece;
	struct Piece{
		float x;
		float y;
		
		int tailleCote;
		
		int visible;
		
		int imgActuelle;
		u16* img[6];
	};
	
	typedef struct Piege Piege;
	struct Piege{
		float x;
		float y;
		
		int tailleCote;
		
		int animation;
		
		int imgActuelle;
		u16* img[9];
	};
		
	enum {STOP, DROITE, GAUCHE, SAUT};
	enum {X,Y};
	enum {HAUT, BAS};