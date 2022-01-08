#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <math.h>
#include "constantes.h"
#include "texture.h"


void animationFinPartie(int carte[][NB_CASES], int *marioGenere, double espaceVideW, double espaceVideH, int coteRedimensionne, SDL_Texture *textureBouton, SDL_Rect *destinationBouton, SDL_Texture *textureSprite[], Rect destinationSprite[], SDL_Texture *textureMenu, SDL_Texture *textureFlecheMenu, SDL_Texture *textureBlack, SDL_Texture *textureVictoire, SDL_Rect *destinationMenu, SDL_Rect *destinationFlecheMenu, SDL_Rect *destinationBlack, SDL_Rect *destinationVictoire, int mode, SDL_Window *window, SDL_Renderer *renderer)
{
    int i;

    SDL_RenderCopy(renderer, textureSprite[MARIO], 0, &destinationSprite[MARIO].jouer);

    copieTableauTexture(textureBouton, NULL, destinationBouton, NULL, NB_BOUTONS, NULL, renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(700);

    for(i = 0; i < 255; i++)
    {
        SDL_RenderClear(renderer);

        chargerPartie(carte, marioGenere, espaceVideW, espaceVideH, coteRedimensionne, textureSprite, destinationSprite, mode, window, renderer);
        SDL_RenderCopy(renderer, textureSprite[MARIO], 0, &destinationSprite[MARIO].jouer);
        copieTableauTexture(textureBouton, NULL, destinationBouton, NULL, NB_BOUTONS, NULL, renderer);

        SDL_SetTextureAlphaMod(textureBlack, i);
        SDL_SetTextureAlphaMod(textureVictoire, i);
        SDL_RenderCopy(renderer, textureBlack, 0, destinationBlack);
        SDL_RenderCopy(renderer, textureVictoire, 0, destinationVictoire);

        SDL_RenderPresent(renderer);
        SDL_Delay(DELAI);
    }

    SDL_Delay(2000);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(i = 254; i > 0; i = i-2)
    {
        SDL_RenderClear(renderer);

        SDL_SetTextureAlphaMod(textureBlack, i);
        SDL_SetTextureAlphaMod(textureVictoire, i);

        SDL_RenderCopy(renderer, textureMenu, 0, destinationMenu);
        SDL_RenderCopy(renderer, textureFlecheMenu, 0, destinationFlecheMenu);

        SDL_RenderCopy(renderer, textureBlack, 0, destinationBlack);
        SDL_RenderCopy(renderer, textureVictoire, 0, destinationVictoire);

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
}

void deplacerMario(int carte[][NB_CASES], SDL_Texture *textureBouton[], SDL_Texture *textureSprite[], SDL_Rect *destinationMario, int espaceVideH, int espaceVideW, int coteRedimensionne, int *sauvegarde, SDL_Window *window, SDL_Renderer *renderer)
{
    int ligne[4], cases[4], tempsAttente = 0;
    SDL_Rect ancienneDestinationMario;
    SDL_Texture *textureMario;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    ancienneDestinationMario.x = destinationMario->x;
    ancienneDestinationMario.y = destinationMario->y;

    ligne[0] = cadrerNombre((int)((destinationMario->y - 1 - espaceVideH) / coteRedimensionne), LIGNES);
    ligne[1] = cadrerNombre((int)((destinationMario->y + destinationMario->h + 1 - espaceVideH) / coteRedimensionne), LIGNES);
    ligne[2] = cadrerNombre((int)((destinationMario->y - espaceVideH) / coteRedimensionne), LIGNES);
    ligne[3] = cadrerNombre((int)((destinationMario->y + destinationMario->h - espaceVideH) / coteRedimensionne), LIGNES);

    cases[0] = cadrerNombre((int)((destinationMario->x - espaceVideW) / coteRedimensionne), NB_CASES);
    cases[1] = cadrerNombre((int)((destinationMario->x + destinationMario->w - espaceVideW) / coteRedimensionne), NB_CASES);
    cases[2] = cadrerNombre((int)((destinationMario->x - 1 - espaceVideW) / coteRedimensionne), NB_CASES);
    cases[3] = cadrerNombre((int)((destinationMario->x + destinationMario->w + 1 -espaceVideW) / coteRedimensionne), NB_CASES);

    if (state[SDL_SCANCODE_UP] && destinationMario->y - 1 >= 0 && deplacerJoueur(UP, carte, ligne[0], cases[0], ligne[0], cases[1]))
        destinationMario->y -= 1;
    if (state[SDL_SCANCODE_DOWN] && destinationMario->y + destinationMario->h - 1 <= SDL_GetWindowSurface(window)->h && deplacerJoueur(DOWN, carte, ligne[1], cases[0], ligne[1], cases[1]))
        destinationMario->y += 1;
    if (state[SDL_SCANCODE_LEFT] && destinationMario->x - 1 >= 0  && deplacerJoueur(LEFT, carte, ligne[2], cases[2], ligne[3], cases[2]))
        destinationMario->x -= 1;
    if (state[SDL_SCANCODE_RIGHT] && destinationMario->x + destinationMario->w - 1 <= SDL_GetWindowSurface(window)->w && deplacerJoueur(RIGHT, carte, ligne[2], cases[3], ligne[3], cases[3]))
        destinationMario->x += 1;

    if (!ancienneDestinationMario.x - destinationMario->x && ancienneDestinationMario.y - destinationMario->y == 1)
        textureMario = textureSprite[MARIO_HAUT];
    else if (ancienneDestinationMario.x - destinationMario->x == 1 && (ancienneDestinationMario.y - destinationMario->y || !ancienneDestinationMario.y - destinationMario->y))
        textureMario = textureSprite[MARIO_GAUCHE];
    else if (ancienneDestinationMario.x - destinationMario->x == -1 && (ancienneDestinationMario.y - destinationMario->y || !ancienneDestinationMario.y - destinationMario->y))
        textureMario = textureSprite[MARIO_DROITE];
    else
        textureMario = textureSprite[MARIO];

    if (ancienneDestinationMario.x - destinationMario->x != 0 && destinationMario->y - destinationMario->y != 0)
        tempsAttente = DELAI*sqrt(2);
    else
        tempsAttente = DELAI;

    if((ancienneDestinationMario.x - destinationMario->x != 0 || ancienneDestinationMario.y - destinationMario->y != 0) && *sauvegarde)
    {
        textureBouton[SAUVEGARDE] = textureBouton[SAUVEGARDER];
        *sauvegarde = 0;
    }

    SDL_RenderCopy(renderer, textureMario, 0, destinationMario);
    SDL_Delay(tempsAttente);
}

int deplacerJoueur(int direction, int carte[][NB_CASES], int ligne, int caseMap, int ligne2, int caseMap2)
{
    int avancer = 1, pos, pos2, i = 0, nombre1 = 0, nombre2 = 0, valeurCase, valeurLigne, finCarte = 0;

    for(i = 0; i < 2; i++)
    {
        if(i == 1)
        {
            valeurLigne = ligne;
            valeurCase = caseMap;
        }
        else
        {
            valeurLigne = ligne2;
            valeurCase = caseMap2;
        }

        pos = carte[valeurLigne][valeurCase];

        if(direction == UP)
        {
            nombre1 = -1;
            pos2 = carte[valeurLigne + nombre1][valeurCase];
            if (valeurLigne + nombre1 < 0)
                finCarte = 1;
        }
        else if(direction == DOWN)
        {
            nombre1 = 1;
            pos2 = carte[valeurLigne + nombre1][valeurCase];
            if (valeurLigne + nombre1 > LIGNES - 1)
                finCarte = 1;
        }
        else if(direction == LEFT)
        {
            nombre2 = -1;
            pos2 = carte[valeurLigne][valeurCase + nombre2];
            if (valeurCase + nombre2 < 0)
                finCarte = 1;
        }
        else
        {
            nombre2 = 1;
            pos2 = carte[valeurLigne][valeurCase + nombre2];
            if (valeurCase + nombre2 > NB_CASES - 1)
                finCarte = 1;
        }

        if (pos == MUR || (pos == CAISSE || pos == CAISSE_OK) && (pos2 == CAISSE || finCarte || pos2 == MUR || pos2 == CAISSE_OK))
            avancer = 0;

        if ((pos == CAISSE || pos == CAISSE_OK) && avancer)
        {
            if(pos == CAISSE)
                carte[valeurLigne][valeurCase] = VIDE;
            else
                carte[valeurLigne][valeurCase] = OBJECTIF;

            if (pos2 == OBJECTIF)
                carte[valeurLigne+nombre1][valeurCase+nombre2] = CAISSE_OK;
            else
                carte[valeurLigne+nombre1][valeurCase+nombre2] = CAISSE;
        }
    }


    return avancer;
}

void remplirEspaceVide(int carte[][NB_CASES], double espaceVideW, double espaceVideH, int coteRedimensionne, SDL_Texture *textureMur, SDL_Rect *destinationMur, SDL_Renderer *renderer)
{
    int i, j, h;
    double espaceVide = espaceVideW;

    for(h = 0; espaceVide > 0; h++)
    {
        for(i = 0; i < LIGNES; i++)
        {
            destinationMur->y = coteRedimensionne * i + espaceVideH;

            if (carte[i][0] == MUR)
            {
                destinationMur->x = espaceVide - coteRedimensionne;
                SDL_RenderCopy(renderer, textureMur, 0, destinationMur);
            }

            if (carte[i][NB_CASES-1] == MUR)
            {
                destinationMur->x = espaceVide + coteRedimensionne * (NB_CASES + h * 2);
                SDL_RenderCopy(renderer, textureMur, 0, destinationMur);
            }
        }

        espaceVide -= coteRedimensionne;
    }

    espaceVide = espaceVideH;
    for(i = 0; espaceVide > 0; i++)
    {
        for(j = -h; j < NB_CASES + h; j++)
        {
            destinationMur->x = coteRedimensionne * j + espaceVideW;

            if (!(carte[0][j] != MUR && j >= 0 && j < NB_CASES))
            {
                destinationMur->y = espaceVide - coteRedimensionne;
                SDL_RenderCopy(renderer, textureMur, 0, destinationMur);
            }

            if (!(carte[LIGNES-1][j] != MUR && j >= 0 && j < NB_CASES))
            {
                destinationMur->y = espaceVide + coteRedimensionne * (LIGNES + i * 2);
                SDL_RenderCopy(renderer, textureMur, 0, destinationMur);
            }
        }

        espaceVide -= coteRedimensionne;
    }
}

int chargerPartie(int carte[][NB_CASES], int *marioGenere, double espaceVideW, double espaceVideH, int coteRedimensionne, SDL_Texture *textureSprite[], Rect destinationSprite[], int mode, SDL_Window *window, SDL_Renderer *renderer)
{
    int i, j, objectifs;
    double coordonneeX, coordonneeY;
    SDL_Rect sprites[NB_SPRITES_MODIFIER];

    for(i = 0; i < NB_SPRITES_MODIFIER; i++)
        sprites[i] = (mode == JOUER) ? destinationSprite[i].jouer : destinationSprite[i].carteEditeur;

    remplirEspaceVide(carte, espaceVideW, espaceVideH, coteRedimensionne, textureSprite[MUR], &sprites[MUR], renderer);

    if (mode == EDITEUR)
        *marioGenere = 0;

    objectifs = 0;
    for (i = 0; i < LIGNES; i++)
    {
        for (j = 0; j < NB_CASES; j++)
        {
            coordonneeX = coteRedimensionne*j+(SDL_GetWindowSurface(window)->w-coteRedimensionne*NB_CASES)/2.0;
            coordonneeY = coteRedimensionne*i+espaceVideH;

            if(!*marioGenere || carte[i][j] != MARIO && carte[i][j] <= NB_SPRITES_MODIFIER)
            {
                if (carte[i][j] == MARIO)
                {
                    coordonneeX += (coteRedimensionne - sprites[MARIO].w)/2;
                    coordonneeY += (coteRedimensionne - sprites[MARIO].h)/2;
                    *marioGenere = 1;
                }

                if (carte[i][j] != VIDE)
                {
                    sprites[carte[i][j]].x = coordonneeX;
                    sprites[carte[i][j]].y = coordonneeY;
                    SDL_RenderCopy(renderer, textureSprite[carte[i][j]], 0, &sprites[carte[i][j]]);
                }

                if (carte[i][j] == MARIO && mode == JOUER)
                    destinationSprite[MARIO].jouer = sprites[MARIO];
            }

            if(carte[i][j] == OBJECTIF)
                objectifs = 1;
        }
    }

    return objectifs;
}
