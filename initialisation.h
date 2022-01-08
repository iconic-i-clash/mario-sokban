#ifndef DEF_INITIALISATION
#define DEF_INITIALISATION

    void genererBouton(SDL_Rect destinationBouton[], int distanceBord, int coteBouton, int largeurFenetre);
    void initialiserSprites(SDL_Texture *textureMario, Rect destinationSprite[], int coteRedimensionne[], int hauteurFenetreEditeur, int espaceVideW, int largeurFenetre, int espaceMenuEdition, SDL_Rect destinationCarreEditeur[]);
    void initialiserCouleur(Couleur *couleur, int r, int g, int b);
    void reinitialiser(int carte[][NB_CASES]);

#endif
