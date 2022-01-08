#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include "constantes.h"
#include "menu.h"
#include "jeu.h"
#include "editeur.h"
#include "texture.h"
#include "initialisation.h"
#include "fichier.h"

//BUG choix mode et animationsFinPartie

int main(int argc, char *argv[])
{
    double espaceVideW[2], espaceVideH[2];
    int sauvegarde = 0, hauteurFenetreEditeur, longueur, ajouterMur = 0, ajouter = 0, effacer = 0, coteRedimensionne[3], boucleCroissante, retourMenu, marioGenere = 0, tempsActuel = 0, tempsPrecedent = 0, carte[LIGNES][NB_CASES], continuer = 1, i = 0, jouer, idCarreSelectionne;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    SDL_Texture *textureSprite[NB_SPRITES], *textureBouton[NB_TEXTURE_BOUTONS], *textureMenuPauseEditeur, *textureCarreEditeur, *textureCarreSelectionneEditeur, *textureFlecheMenu, *textureBlack, *textureMenuPause, *textureVictoire, *textureMenu;
    SDL_Rect destinationCarreEditeur[NB_CARRE_EDITEUR], destinationBouton[NB_BOUTONS], destinationFlecheMenu, zoneMenuEditeur, delimitationZoneModifiable[LARGEUR_DELIMITATION_ZONE], destinationBoutonsMenuPause, destinationBlack, destinationMenuPause, destinationVictoire, destinationMenu;
    Couleur couleur[3];
    Rect destinationSprite[NB_SPRITES_MODIFIER];
    char *nomSprite[] = {"mur.jpg", "objectif.png", "mario_bas.gif", "caisse.jpg", "caisse_ok.jpg", "mario_haut.gif", "mario_gauche.gif", "mario_droite.gif"}, *nomBouton[] = {"pause.png", "enregistrement.png", "information.png", "pauseEditeur.png", "enregistrementReussi.png", "enregistrement.png"};

    creationFenetre("Mario Sokoban - Iconic I Clash", "logo.png", &window, &renderer);

    textureMenu = genererTexture("menu.png", renderer);
    destinationMenu = centrerImage(textureMenu, destinationMenu, window, NULL);

    if (SDL_GetWindowSurface(window)->h < SDL_GetWindowSurface(window)->w)
        longueur = SDL_GetWindowSurface(window)->h;
    else
        longueur = SDL_GetWindowSurface(window)->w;

    textureFlecheMenu = genererTexture("triangle.png", renderer);
    redimensionner(&destinationFlecheMenu, longueur*38/705, NULL);
    destinationFlecheMenu.x = destinationMenu.x + 0.23 * destinationMenu.w;

    jouer = chargementMenu(renderer, textureMenu, &destinationMenu, textureFlecheMenu, &destinationFlecheMenu, 1);

    hauteurFenetreEditeur = 0.85*SDL_GetWindowSurface(window)->h;
    textureCarreSelectionneEditeur = genererTexture("carreSelectionne.png", renderer);

    genererBouton(destinationBouton, longueur*18/705, longueur*42/705, SDL_GetWindowSurface(window)->w);
    modificationTextures(textureSprite, nomSprite, NB_SPRITES, renderer);
    modificationTextures(textureBouton, nomBouton, NB_TEXTURE_BOUTONS, renderer);

    textureMenuPause = genererTexture("menu-pause.png", renderer);
    textureMenuPauseEditeur = genererTexture("menuPause.png", renderer);
    destinationMenuPause = centrerImage(textureMenuPause, destinationMenuPause, window, &destinationBoutonsMenuPause);

    textureBlack = genererTexture("black.png", renderer);
    SDL_QueryTexture(textureBlack, NULL, NULL, &destinationBlack.w, &destinationBlack.h);
    destinationBlack.x = (SDL_GetWindowSurface(window)->w-destinationBlack.w)/2;
    destinationBlack.y = (SDL_GetWindowSurface(window)->h-destinationBlack.h)/2;

    textureVictoire = genererTexture("victoire.png", renderer);
    destinationVictoire = centrerImage(textureVictoire, destinationVictoire, window, NULL);

    initialiserCouleur(&couleur[1], 255, 248, 240);
    initialiserCouleur(&couleur[2], 242, 212, 170);

    coteRedimensionne[JOUER] = COTE*inverseProportionDimensions(SDL_GetWindowSurface(window)->h, SDL_GetWindowSurface(window)->w, COTE*LIGNES, COTE*NB_CASES);
    coteRedimensionne[EDITEUR] = (SDL_GetWindowSurface(window)->h-hauteurFenetreEditeur)/2;
    coteRedimensionne[CARTE_EDITEUR] = COTE*inverseProportionDimensions(hauteurFenetreEditeur, SDL_GetWindowSurface(window)->w, COTE*LIGNES, COTE*NB_CASES);

    textureCarreEditeur = genererTexture("carre.png", renderer);

    espaceVideW[JOUER] = (SDL_GetWindowSurface(window)->w - coteRedimensionne[JOUER] * NB_CASES)/2.0;
    espaceVideH[JOUER] = (SDL_GetWindowSurface(window)->h - coteRedimensionne[JOUER] * LIGNES)/2.0;
    espaceVideW[EDITEUR] = (SDL_GetWindowSurface(window)->w - coteRedimensionne[CARTE_EDITEUR] * NB_CASES)/2.0;
    espaceVideH[EDITEUR] = (hauteurFenetreEditeur - coteRedimensionne[CARTE_EDITEUR] * LIGNES)/2.0;

    initialiserSprites(textureSprite[MARIO], destinationSprite, coteRedimensionne, hauteurFenetreEditeur, espaceVideW[EDITEUR], SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h - hauteurFenetreEditeur, destinationCarreEditeur);
    rectangleCouleurs(delimitationZoneModifiable, coteRedimensionne[CARTE_EDITEUR], espaceVideH[EDITEUR], espaceVideW[EDITEUR]);

    zoneMenuEditeur.y = hauteurFenetreEditeur;
    zoneMenuEditeur.h = SDL_GetWindowSurface(window)->h-hauteurFenetreEditeur;
    zoneMenuEditeur.x = espaceVideW[EDITEUR];
    zoneMenuEditeur.w = SDL_GetWindowSurface(window)->w - 2*espaceVideW[EDITEUR];

    /*dimensionsCarteEditeur.y = espaceVideH[EDITEUR];
    dimensionsCarteEditeur.x = zoneMenuEditeur.x;
    dimensionsCarteEditeur.h = hauteurFenetreEditeur;
    dimensionsCarteEditeur.w = zoneMenuEditeur.w;*/


    while (continuer) {

        if (SDL_WaitEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;

                        case SDLK_UP:
                            jouer = chargementMenu(renderer, textureMenu, &destinationMenu, textureFlecheMenu, &destinationFlecheMenu, 1);
                            break;

                        case SDLK_DOWN:
                            destinationFlecheMenu.y = destinationMenu.y + 0.592 * destinationMenu.h;
                            jouer = chargementMenu(renderer, textureMenu, &destinationMenu, textureFlecheMenu, &destinationFlecheMenu, 0);
                            break;

                        case SDLK_1:

                            SDL_SetTextureAlphaMod(textureBlack, 100);

                            if (jouer)
                            {
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                                retourMenu = genererPartie(carte, renderer);
                                marioGenere = 0;
                                retourMenu = 0;

                                while (continuer) {

                                    //fonction
                                    while(SDL_PollEvent(&event))
                                    {
                                        retourMenu = appelMenuPause(&event, &continuer, carte, textureMenuPause, &destinationMenuPause, textureMenu, &destinationMenu, textureBlack, &destinationBlack, destinationBoutonsMenuPause, &marioGenere, textureFlecheMenu, &destinationFlecheMenu, textureBouton, destinationBouton, &sauvegarde, JOUER, window, renderer);
                                        if (!continuer || retourMenu)
                                            break;
                                    }

                                    if (!continuer || retourMenu)
                                        break;
                                    //fonction

                                    SDL_RenderClear(renderer);

                                    if (!chargerPartie(carte, &marioGenere, espaceVideW[JOUER], espaceVideH[JOUER], coteRedimensionne[JOUER], textureSprite, &destinationSprite, JOUER, window, renderer))
                                    {
                                        animationFinPartie(carte, &marioGenere, espaceVideW[JOUER], espaceVideH[JOUER], coteRedimensionne[JOUER], textureBouton, &destinationBouton, textureSprite, &destinationSprite, textureMenu, textureFlecheMenu, textureBlack, textureVictoire, &destinationMenu, &destinationFlecheMenu, &destinationBlack, &destinationVictoire, JOUER, window, renderer);
                                        break;
                                    }

                                    deplacerMario(carte, textureBouton, textureSprite, &destinationSprite[MARIO].jouer, espaceVideH[JOUER], espaceVideW[JOUER], coteRedimensionne[JOUER], &sauvegarde, window, renderer);
                                    copieTableauTexture(textureBouton, NULL, destinationBouton, NULL, NB_BOUTONS, NULL, renderer);

                                    SDL_RenderPresent(renderer);
                                }
                            }
                            else
                            {
                                //SDL_Delay(200);
                                //Solution temporaire au bug de if(0)

                                reinitialiser(carte);
                                initialiserCouleur(&couleur[0], 245, 215, 177);

                                boucleCroissante = 1;
                                tempsPrecedent = 0;
                                marioGenere = 0;
                                ajouterMur = 0;
                                ajouter = VIDE;
                                effacer = 0;
                                idCarreSelectionne = VIDE;

                                while (continuer)
                                {
                                    while(SDL_PollEvent(&event))
                                    {
                                        modifierCarteEditeur(event, carte, textureBouton, destinationBouton, destinationCarreEditeur, &idCarreSelectionne, espaceVideH[EDITEUR], espaceVideW[EDITEUR], coteRedimensionne[CARTE_EDITEUR], &ajouter, &ajouterMur, &marioGenere, &effacer, &sauvegarde);
                                        retourMenu = appelMenuPause(&event, &continuer, carte, textureMenuPauseEditeur, &destinationMenuPause, textureMenu, &destinationMenu, textureBlack, &destinationBlack, destinationBoutonsMenuPause, &marioGenere, textureFlecheMenu, &destinationFlecheMenu, textureBouton, destinationBouton, &sauvegarde, EDITEUR, window, renderer);

                                        if (!continuer || retourMenu)
                                            break;
                                    }

                                    if (!continuer || retourMenu)
                                        break;

                                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                    SDL_RenderClear(renderer);

                                    chargerPartie(carte, &marioGenere, espaceVideW[EDITEUR], espaceVideH[EDITEUR], coteRedimensionne[CARTE_EDITEUR], textureSprite, &destinationSprite, EDITEUR, window, renderer);
                                    animationsEditeur(couleur, &boucleCroissante, &tempsPrecedent, &zoneMenuEditeur, delimitationZoneModifiable, espaceVideW[EDITEUR], hauteurFenetreEditeur, window, renderer);

                                    copieTableauTexture(textureBouton, NULL, &destinationBouton, NULL, BOUTONS_EDITEUR, NULL, renderer);
                                    copieTableauTexture(&textureCarreEditeur, textureCarreSelectionneEditeur, &destinationCarreEditeur, NULL, NB_CARRE_EDITEUR, idCarreSelectionne+1, renderer);
                                    copieTableauTexture(textureSprite, NULL, NULL, &destinationSprite, NB_SPRITES_MODIFIER, NULL, renderer);

                                    SDL_RenderPresent(renderer);

                                    if (!effacer && !ajouterMur)
                                        SDL_Delay(10);
                                    else
                                        SDL_Delay(1);
                                }
                            }

                            if (continuer)
                                jouer = chargementMenu(renderer, textureMenu, &destinationMenu, textureFlecheMenu, &destinationFlecheMenu, 2);
                            break;
                    }
                    break;
            }
        }
    }

    SDL_DestroyTexture(textureMenuPauseEditeur);
    SDL_DestroyTexture(textureMenuPause);
    SDL_DestroyTexture(textureCarreEditeur);
    SDL_DestroyTexture(textureCarreSelectionneEditeur);
    SDL_DestroyTexture(textureFlecheMenu);
    SDL_DestroyTexture(textureBlack);
    SDL_DestroyTexture(textureMenu);
    SDL_DestroyTexture(textureVictoire);
    modificationTextures(textureSprite, NULL, NB_SPRITES, renderer);
    modificationTextures(textureBouton, NULL, NB_TEXTURE_BOUTONS, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}


void creationFenetre(char *titre, char *nomFichierLogo, SDL_Window **window, SDL_Renderer **renderer)
{
    SDL_Surface *logo;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        messageError("Erreur d'initialisation", "Impossible d'initialiser la bibliotheque SDL : ");

    if (SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_MAXIMIZED|SDL_WINDOW_RESIZABLE, window, renderer))
        messageError("Erreur de chargement", "Impossible de charger la fenetre ou le moteur de rendu : ");

    SDL_SetWindowTitle(*window, titre);
    logo = IMG_Load(nomFichierLogo);
    SDL_SetWindowIcon(*window, logo);
    SDL_FreeSurface(logo);

    SDL_SetWindowMinimumSize(*window, SDL_GetWindowSurface(*window)->w, SDL_GetWindowSurface(*window)->h);
}

int cadrerNombre(int nombre, int limite)
{
    if(nombre < 0)
        nombre = 0;
    else
    {
        if(nombre > limite - 1)
            nombre = limite - 1;
    }

    return nombre;
}

void messageError(char *titre, char *contenu)
{
    char string[100];
    strcpy(string, contenu);

    strcat(string, SDL_GetError());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, titre, string, NULL);
    exit(EXIT_FAILURE);
}
