#ifndef DEF_JEU
#define DEF_JEU

    void remplirEspaceVide(int carte[][NB_CASES], double espaceVideW, double espaceVideH, int coteRedimensionne, SDL_Texture *textureMur, SDL_Rect *destinationMur, SDL_Renderer *renderer);
    int chargerPartie(int carte[][NB_CASES], int *marioGenere, double espaceVideW, double espaceVideH, int coteRedimensionne, SDL_Texture *textureSprite[], Rect destinationSprite[], int mode, SDL_Window *window, SDL_Renderer *renderer);
    int deplacerJoueur(int direction, int carte[][NB_CASES], int ligne, int caseMap, int ligne2, int caseMap2);
    void deplacerMario(int carte[][NB_CASES], SDL_Texture *textureBouton[], SDL_Texture *textureSprite[], SDL_Rect *destinationMario, int espaceVideH, int espaceVideW, int coteRedimensionne, int *sauvegarde, SDL_Window *window, SDL_Renderer *renderer);
    void animationFinPartie(int carte[][NB_CASES], int *marioGenere, double espaceVideW, double espaceVideH, int coteRedimensionne, SDL_Texture *textureBouton, SDL_Rect *destinationBouton, SDL_Texture *textureSprite[], Rect destinationSprite[], SDL_Texture *textureMenu, SDL_Texture *textureFlecheMenu, SDL_Texture *textureBlack, SDL_Texture *textureVictoire, SDL_Rect *destinationMenu, SDL_Rect *destinationFlecheMenu, SDL_Rect *destinationBlack, SDL_Rect *destinationVictoire, int mode, SDL_Window *window, SDL_Renderer *renderer);


#endif
