#ifndef DEF_TEXTURE
#define DEF_TEXTURE

    SDL_Texture *genererTexture(char* nomTexture, SDL_Renderer* renderer);
    SDL_Rect centrerImage(SDL_Texture *textureImage, SDL_Rect destinationImage, SDL_Window *window, SDL_Rect *destinationBouttonsMenuPause);
    double inverseProportionDimensions(int hauteurFenetre, int largeurFenetre, int hauteurStructure, int largeurStructure);
    void redimensionner(SDL_Rect *destinationStructure, int coteRedimensionne, SDL_Texture *textureImage);
    void copieTableauTexture(SDL_Texture *texture[], SDL_Texture *textureCarreSelectionne, SDL_Rect destination[], Rect sprites[],  int tailleTableau, int idCarreSelectionne, SDL_Renderer *renderer);
    void modificationTextures(SDL_Texture *textureSprite[], char *nomSprite[], int longueur, SDL_Renderer *renderer);

#endif
