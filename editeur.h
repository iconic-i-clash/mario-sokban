#ifndef DEF_EDITEUR
#define DEF_EDITEUR

    void animationCouleurs(Couleur *couleur, int* boucleCouleur);
    void rectangleCouleurs(SDL_Rect rectangle[], int coteRedimensionne, int espaceVideH, int espaceVideW);
    void animationsEditeur(Couleur couleur[], int *boucleCroissante, int *tempsPrecedent, SDL_Rect *zoneMenuEditeur, SDL_Rect delimitationZoneModifiable[], int espaceVideW, int hauteurFenetreEditeur, SDL_Window *window, SDL_Renderer *renderer);
    void modifierCarteEditeur(SDL_Event event, int carte[][NB_CASES], SDL_Texture *textureBouton[], SDL_Rect destinationBouton[], SDL_Rect destinationCarreEditeur[], int *idCarreSelectionne, int espaceVideH, int espaceVideW, int coteRedimensionne, int *ajouter, int *ajouterMur, int *marioGenere, int *effacer, int *sauvegarde);

#endif
