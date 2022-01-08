#ifndef DEF_FICHIER
#define DEF_FICHIER

    void messageErreurFichier(char *title, char *message, int* buttonId);
    int genererPartie(int carte[][NB_CASES], SDL_Renderer *renderer);
    void traiterErreurFichier(int *butonId, char *nomFichier, char *fichierInitial);

#endif
