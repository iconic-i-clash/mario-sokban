#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "constantes.h"


void modifierCarteEditeur(SDL_Event event, int carte[][NB_CASES], SDL_Texture *textureBouton[], SDL_Rect destinationBouton[], SDL_Rect destinationCarreEditeur[], int *idCarreSelectionne, int espaceVideH, int espaceVideW, int coteRedimensionne, int *ajouter, int *ajouterMur, int *marioGenere, int *effacer, int *sauvegarde)
{
    int ligne, cases, i, bouton = 0, modification = 0;

    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT && !*effacer)
        {
            ligne = (event.button.y-espaceVideH)/coteRedimensionne;
            cases = (event.button.x-espaceVideW)/coteRedimensionne;

            if (event.button.y - destinationCarreEditeur[0].y >= 0 && event.button.y <= destinationCarreEditeur[0].y + destinationCarreEditeur[0].h)
            {
                for (i = 0; i < NB_CARRE_EDITEUR; i++)
                {
                    if (event.button.x - destinationCarreEditeur[i].x >= 0 && event.button.x <= destinationCarreEditeur[i].x + destinationCarreEditeur[i].w)
                    {
                        if (i != MARIO || i == MARIO && !*marioGenere)
                            *idCarreSelectionne = i;
                        else
                            *idCarreSelectionne = VIDE;

                        *ajouter = i;
                        modification = 1;
                    }
                }
            }
            else
            {
                for (i = 0; i < NB_BOUTONS; i++)
                {
                    if (event.button.y >= destinationBouton[i].y && event.button.y <= destinationBouton[i].y+destinationBouton[i].h && event.button.x >= destinationBouton[i].x && event.button.x < destinationBouton[i].x+destinationBouton[i].w)
                        bouton = 1;
                }

                if (ligne >= 0 && ligne < LIGNES && cases >= 0 && cases < NB_CASES && !bouton)
                {
                    if (*ajouter == MARIO)
                    {
                        if (!*marioGenere)
                            carte[ligne][cases] = *ajouter;

                        *idCarreSelectionne = VIDE;
                    }

                    if (*ajouter != VIDE && *ajouter != MARIO)
                        carte[ligne][cases] = *ajouter;

                    if (*ajouter == MUR)
                        *ajouterMur = 1;

                    if (*ajouter != VIDE)
                        modification = 1;
                }
            }
        }

        if (event.button.button == SDL_BUTTON_RIGHT && !*ajouterMur)
        {
            *effacer = 1;
            modification = 1;

            ligne = cadrerNombre((int)((event.button.y-espaceVideH)/coteRedimensionne), LIGNES);
            cases = cadrerNombre((int)((event.button.x-espaceVideW)/coteRedimensionne), NB_CASES);

            EFFACER_MARIO()
        }
    }

    if(event.type == SDL_MOUSEBUTTONUP)
    {
        if (*effacer && event.button.button == SDL_BUTTON_RIGHT)
            *effacer = 0;

        if (*ajouterMur && event.button.button == SDL_BUTTON_LEFT)
            *ajouterMur = 0;
    }

    if (event.type == SDL_MOUSEMOTION)
    {
        ligne = cadrerNombre((int)((event.motion.y-espaceVideH)/coteRedimensionne), LIGNES);
        cases = cadrerNombre((int)((event.motion.x-espaceVideW)/coteRedimensionne), NB_CASES);

        if (*effacer)
        {
            EFFACER_MARIO()
        }

        if(*ajouterMur)
            carte[ligne][cases] = MUR;

        if (*effacer || *ajouterMur)
            modification = 1;
    }

    if (*sauvegarde && modification)
    {
        *sauvegarde = 0;
        textureBouton[SAUVEGARDE] = textureBouton[SAUVEGARDER];
    }
}

void animationsEditeur(Couleur couleur[], int *boucleCroissante, int *tempsPrecedent, SDL_Rect *zoneMenuEditeur, SDL_Rect delimitationZoneModifiable[], int espaceVideW, int hauteurFenetreEditeur, SDL_Window *window, SDL_Renderer *renderer)
{
    int tempsActuel = SDL_GetTicks(), i;

    if (tempsActuel - *tempsPrecedent > 70)
    {
        animationCouleurs(&couleur[0], boucleCroissante);
        *tempsPrecedent = tempsActuel;
    }

    SDL_SetRenderDrawColor(renderer, couleur[0].r, couleur[0].g, couleur[0].b, 255);

    for (i = 0; i < LARGEUR_DELIMITATION_ZONE; i++)
        SDL_RenderDrawRect(renderer, &delimitationZoneModifiable[i]);

    SDL_SetRenderDrawColor(renderer, couleur[1].r, couleur[1].g, couleur[1].b, 255);
    SDL_RenderFillRect(renderer, zoneMenuEditeur);

    for(i = 0; i < espaceVideW+1; i++)
    {
        SDL_SetRenderDrawColor(renderer, couleur[1].r-((couleur[1].r-couleur[2].r)*i/(espaceVideW+1)), couleur[1].g-((couleur[1].g-couleur[2].g)*i/(espaceVideW+1)), couleur[1].b-((couleur[1].b-couleur[2].b)*i/(espaceVideW+1)), 255);
        SDL_RenderDrawLine(renderer, espaceVideW-i, hauteurFenetreEditeur, espaceVideW-i, SDL_GetWindowSurface(window)->h);
        SDL_RenderDrawLine(renderer, SDL_GetWindowSurface(window)->w-espaceVideW+i, hauteurFenetreEditeur, SDL_GetWindowSurface(window)->w-espaceVideW+i, SDL_GetWindowSurface(window)->h);
    }
}

void animationCouleurs(Couleur *couleur, int* boucleCouleur)
{
    int valeurs[3] = {couleur->r, couleur->g, couleur->b}, i;

    for (i = 0; i < 3; i++)
    {
        if (valeurs[i] == 0)
            *boucleCouleur = 1;

        if (valeurs[i] == 255)
            *boucleCouleur = 0;

        if (*boucleCouleur)
            valeurs[i]++;
        else
            valeurs[i]--;
    }

    couleur->r = valeurs[0];
    couleur->g = valeurs[1];
    couleur->b = valeurs[2];
}

void rectangleCouleurs(SDL_Rect rectangle[], int coteRedimensionne, int espaceVideH, int espaceVideW)
{
    int i;

    for (i = 0; i < LARGEUR_DELIMITATION_ZONE; i ++)
    {
        rectangle[i].x = espaceVideW+i;
        rectangle[i].y = espaceVideH+i;
        rectangle[i].w = coteRedimensionne * NB_CASES-i*2;
        rectangle[i].h = coteRedimensionne * LIGNES-i*2;
    }
}
