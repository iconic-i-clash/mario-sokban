#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "constantes.h"

double inverseProportionDimensions(int hauteurFenetre, int largeurFenetre, int hauteurStructure, int largeurStructure)
{
    double proportionLargeur = largeurStructure/(double)largeurFenetre;
    double proportionHauteur = hauteurStructure/(double)hauteurFenetre;

    if (proportionLargeur >= proportionHauteur)
        return 1.0/proportionLargeur;
    else
        return 1.0/proportionHauteur;
}

SDL_Rect centrerImage(SDL_Texture *textureImage, SDL_Rect destinationImage, SDL_Window *window, SDL_Rect *destinationBouttonsMenuPause)
{
    SDL_QueryTexture(textureImage, NULL, NULL, &destinationImage.w, &destinationImage.h);
    double inverseProportion = inverseProportionDimensions(SDL_GetWindowSurface(window)->h, SDL_GetWindowSurface(window)->w, destinationImage.h, destinationImage.w);

    destinationImage.w *= inverseProportion;
    destinationImage.h *= inverseProportion;
    destinationImage.x = (SDL_GetWindowSurface(window)->w-destinationImage.w)/2;
    destinationImage.y = (SDL_GetWindowSurface(window)->h-destinationImage.h)/2;

    if (destinationBouttonsMenuPause != NULL)
    {
        destinationBouttonsMenuPause->w = 1130*inverseProportion;
        destinationBouttonsMenuPause->h = 200*inverseProportion;
        destinationBouttonsMenuPause->x = 718*inverseProportion + destinationImage.x;
        destinationBouttonsMenuPause->y = 1186*inverseProportion + destinationImage.y;
    }

    return destinationImage;
}

SDL_Texture *genererTexture(char* nomTexture, SDL_Renderer* renderer)
{
    SDL_Surface *image;
    SDL_Texture *textureImage;

    image = IMG_Load(nomTexture);
    textureImage = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return textureImage;
}

void copieTableauTexture(SDL_Texture *texture[], SDL_Texture *textureCarreSelectionne, SDL_Rect destination[], Rect sprites[], int tailleTableau, int idCarreSelectionne, SDL_Renderer *renderer)
{
    int i;

    if (tailleTableau == BOUTONS_EDITEUR)
    {
        texture[0] = texture[PAUSE_EDITEUR];
        tailleTableau = NB_BOUTONS;
    }

    for (i = 0; i < tailleTableau; i++)
    {
        if (destination == NULL)
            SDL_RenderCopy(renderer, texture[i], 0, &sprites[i].editeur);
        else if (idCarreSelectionne != NULL)
        {
            if (i == idCarreSelectionne-1)
                SDL_RenderCopy(renderer, textureCarreSelectionne, 0, &destination[i]);
            else
                SDL_RenderCopy(renderer, *texture, 0, &destination[i]);
        }
        else
            SDL_RenderCopy(renderer, texture[i], 0, &destination[i]);
    }
}

void modificationTextures(SDL_Texture *textureSprite[], char *nomSprite[], int longueur, SDL_Renderer *renderer)
{
    int i;

    for(i = 0; i < longueur; i++)
    {
        if (nomSprite == NULL)
            SDL_DestroyTexture(textureSprite[i]);
        else
            textureSprite[i] = genererTexture(nomSprite[i], renderer);
    }
}

void redimensionner(SDL_Rect *destinationStructure, int coteRedimensionne, SDL_Texture *textureImage)
{
    if (textureImage == NULL)
    {
        destinationStructure->w = coteRedimensionne;
        destinationStructure->h = coteRedimensionne;
    }
    else
    {
        SDL_QueryTexture(textureImage, NULL, NULL, &destinationStructure->w, &destinationStructure->h);

        destinationStructure->w = destinationStructure->w * coteRedimensionne/COTE;
        destinationStructure->h = destinationStructure->h * coteRedimensionne/COTE;
    }
}
