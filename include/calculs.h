	
	void deplacementPerso(Perso* persoHaut, Perso* persoBas, int persoActuel, int direction);
	int collisionSolY(Perso* perso, Sol* plateforme);
	int collisionSolX(Perso* perso, Sol* plateforme);
	int chutePerso (Perso* persoHaut, Perso* persoBas);
	void collisionPiece(Perso* perso, Piece* piece, int* nbPiece);
	void collisionPiege(Perso* perso, Piege* piege);
	void scroll(Perso* perso, Sol* plateforme, Piece* piece, Piege* piege, int ecran);
	int fin(Perso* persoHaut, Perso* persoBas, int persoActuel, int* bg, int* bgSub,  int* nbPiece,  Sol* solHaut, Sol* solBas);