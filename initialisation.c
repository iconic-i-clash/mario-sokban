#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "constantes.h"


void genererBouton(SDL_Rect destinationBouton[], int distanceBord, int coteBouton, int largeurFenetre)
{
    int i;

    redimensionner(&destinationBouton[0], coteBouton, NULL);

    for (i = 0; i < NB_BOUTONS; i ++)
    {
        if (i == 0)
            redimensionner(&destinationBouton[i], coteBouton, NULL);
        else
            destinationBouton[i] = destinationBouton[0];

        destinationBouton[i].x = largeurFenetre - coteBouton - distanceBord - i*((1-ESPACEMENT_BOUTONS)*distanceBord + coteBouton);
        destinationBouton[i].y = distanceBord;
    }
}

void initialiserCouleur(Couleur *couleur, int r, int g, int b)
{
    couleur->r = r;
    couleur->g = g;
    couleur->b = b;
}

void reinitialiser(int carte[][NB_CASES])
{
    int i, j;

    for(i = 0; i < LIGNES; i++)
    {
        for(j = 0; j < NB_CASES; j++)
            carte[i][j] = MUR;
    }
}

void initialiserSprites(SDL_Texture *textureMario, Rect destinationSprite[], int coteRedimensionne[], int hauteurFenetreEditeur, int espaceVideW, int largeurFenetre, int espaceMenuEdition, SDL_Rect destinationCarreEditeur[])
{
    int i, espaceBord = espaceVideW + 180, largeurCarreMenuEdition = coteRedimensionne[EDITEUR]*1.5;
    SDL_Texture *textureNULL = NULL;

    for (i = 0; i < NB_SPRITES_MODIFIER; i++)
    {
        if (i == MARIO)
            textureNULL = textureMario;
        else
            textureNULL = NULL;

        redimensionner(&destinationSprite[i].jouer, coteRedimensionne[JOUER], textureNULL);
        redimensionner(&destinationSprite[i].carteEditeur, coteRedimensionne[CARTE_EDITEUR], textureNULL);
        redimensionner(&destinationSprite[i].editeur, coteRedimensionne[EDITEUR], textureNULL);
        redimensionner(&destinationCarreEditeur[i], largeurCarreMenuEdition, NULL);

        destinationSprite[i].editeur.y = hauteurFenetreEditeur + (espaceMenuEdition - destinationSprite[i].editeur.h)/2;
        destinationSprite[i].editeur.x = espaceBord + (largeurFenetre - 2*espaceBord)/NB_SPRITES_MODIFIER*(i+0.5) - destinationSprite[i].editeur.w/2;
        destinationCarreEditeur[i].y = hauteurFenetreEditeur + (espaceMenuEdition - largeurCarreMenuEdition)/2;
        destinationCarreEditeur[i].x = espaceBord + (largeurFenetre - 2*espaceBord)/NB_SPRITES_MODIFIER*(i+0.5) - largeurCarreMenuEdition/2;
    }
}
