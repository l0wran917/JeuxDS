#include <nds.h>
#include <stdio.h>

#define NBPLATEFORME 25
#define NBPIECEHAUT 12
#define NBPIEGEBAS 12

#include "backgroundJourDebutHaut.h"
#include "backgroundNuitDebutHaut.h"
#include "backgroundJourDebutBas.h"
#include "backgroundNuitDebutBas.h"
#include "backgroundJourGagne.h"
#include "backgroundNuitGagne.h"
#include "backgroundJourPiece.h"
#include "backgroundNuitPiece.h"
#include "backgroundJour.h"
#include "backgroundNuit.h"

#include "chiffre.h"
#include "persoHaut.h"
#include "persoBas.h"
#include "piece.h"
#include "piege.h"
#include "sol.h"


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
		
		int rotation;
		
		int imgActuelle;
		u16* img[5];
	};
	
	typedef struct Piege Piege;
	struct Piege{
		float x;
		float y;
		
		int tailleCote;
		
		int animation;
		int sensAnim;
		
		int imgActuelle;
		u16* img[5];
	};
	
	typedef struct Chiffre Chiffre;
	struct Chiffre{
		float x;
		float y;
		
		u16* img[11];
	};
	
	enum {STOP, DROITE, GAUCHE, SAUT};
	enum {X,Y};
	enum {HAUT, BAS};