	
	void deplacementPerso(Perso* persoHaut, Perso* persoBas, int persoActuel, int direction);
	int collisionSolY(Perso* perso, Sol* plateforme);
	int collisionSolX(Perso* perso, Sol* plateforme);
	void collisionPiece(Perso* perso, Piece* piece);
	void collisionPiege(Perso* perso, Piege* piege);
	void scroll(Perso* perso, Sol* plateforme, Piece* piece, Piege* piege, int ecran);