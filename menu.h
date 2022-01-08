#ifndef DEF_MENU
#define DEF_MENU

    int chargementMenu(SDL_Renderer *renderer, SDL_Texture *textureMenu, SDL_Rect *destinationMenu, SDL_Texture *textureFlecheMenu, SDL_Rect *destinationFlecheMenu, int option);
    int menuPause(int carte[][NB_CASES], int *continuer, SDL_Texture *textureBouton[], SDL_Texture *textureMenuPause, SDL_Rect *destinationMenuPause, SDL_Texture *textureBlack, SDL_Rect *destinationBlack, SDL_Rect destinationBouttonsMenuPause, SDL_Renderer *renderer, SDL_Window *window, int *marioGenere, int mode, int *sauvegarde);
    int appelMenuPause(SDL_Event *event, int *continuer, int carte[][NB_CASES], SDL_Texture *textureMenuPause, SDL_Rect *destinationMenuPause, SDL_Texture *textureMenu, SDL_Rect *destinationMenu, SDL_Texture *textureBlack, SDL_Rect *destinationBlack, SDL_Rect destinationBoutonsMenuPause, int *marioGenere, SDL_Texture *textureFlecheMenu, SDL_Rect *destinationFlecheMenu, SDL_Texture *textureBouton[], SDL_Rect destinationBouton[], int *sauvegarde, int mode, SDL_Window *window, SDL_Renderer *renderer);

#endif
