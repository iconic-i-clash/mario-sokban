#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define NB_CASES 30
    #define LIGNES 16
    #define COTE 34
    #define NB_CARRE_EDITEUR 5
    #define LARGEUR_DELIMITATION_ZONE 4
    #define NB_BOUTONS 3
    #define ESPACEMENT_BOUTONS 0.5
    #define NB_SPRITES 8
    #define NB_SPRITES_MODIFIER 5
    #define NB_TEXTURE_BOUTONS 6
    #define NB_BOUTONS 3
    #define BOUTONS_EDITEUR 100
    #define DELAI 7
    #define EFFACER_MARIO() if (carte[ligne][cases] == MARIO) \
                            { \
                                *marioGenere = 0; \
                                if (*ajouter == MARIO) \
                                    *idCarreSelectionne = MARIO; \
                            } \
                            carte[ligne][cases] = VIDE;

    enum {PAUSE = 0, SAUVEGARDE = 1, INFORMATION = 2, PAUSE_EDITEUR = 3, SAUVEGARDE_REUSSI = 4, SAUVEGARDER = 5, JOUER = 0, EDITEUR = 1, CARTE_EDITEUR = 2, MUR = 0, OBJECTIF = 1, MARIO = 2, CAISSE = 3, CAISSE_OK = 4, MARIO_HAUT = 5, MARIO_GAUCHE = 6, MARIO_DROITE = 7, VIDE = 8, UP, DOWN, LEFT, RIGHT};

    typedef struct Couleur Couleur;
    struct Couleur
    {
        int r;
        int g;
        int b;
    };

    typedef struct Rect Rect;
    struct Rect
    {
        SDL_Rect jouer;
        SDL_Rect carteEditeur;
        SDL_Rect editeur;
    };

    void messageError(char *titre, char *contenu);
    void creationFenetre(char *titre, char *nomFichierLogo, SDL_Window **window, SDL_Renderer **renderer);
    int cadrerNombre(int nombre, int limite);

#endif
