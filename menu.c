#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "constantes.h"
#include "fichier.h"
#include "initialisation.h"


int appelMenuPause(SDL_Event *event, int *continuer, int carte[][NB_CASES], SDL_Texture *textureMenuPause, SDL_Rect *destinationMenuPause, SDL_Texture *textureMenu, SDL_Rect *destinationMenu, SDL_Texture *textureBlack, SDL_Rect *destinationBlack, SDL_Rect destinationBoutonsMenuPause, int *marioGenere, SDL_Texture *textureFlecheMenu, SDL_Rect *destinationFlecheMenu, SDL_Texture *textureBouton[], SDL_Rect destinationBouton[], int *sauvegarde, int mode, SDL_Window *window, SDL_Renderer *renderer)
{
    int retourMenu = 0, i;
    SDL_Surface *screenshot = SDL_CreateRGBSurface(0, SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h, 32, 0, 0, 0, 0);

    if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
        *continuer = 0;

    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
    {
        if (event->button.y >= destinationBouton[0].y && event->button.y <= destinationBouton[0].y + destinationBouton[0].h)
        {
            for (i = 0; i < NB_BOUTONS; i++)
            {
                if(event->button.x >= destinationBouton[i].x && event->button.x <= destinationBouton[i].x + destinationBouton[i].w)
                {
                    switch (i)
                    {
                    case PAUSE:
                        if (!menuPause(carte, continuer, textureBouton, textureMenuPause, destinationMenuPause, textureBlack, destinationBlack, destinationBoutonsMenuPause, renderer, window, marioGenere, mode, sauvegarde))
                            retourMenu = 1;
                        break;

                    case SAUVEGARDE:
                        if (!*sauvegarde)
                        {
                            textureBouton[SAUVEGARDE] = textureBouton[SAUVEGARDE_REUSSI];
                            SDL_RenderReadPixels(renderer, NULL, 0, screenshot->pixels, screenshot->pitch);
                            SDL_SaveBMP(screenshot, "screenshot.bmp");
                            *sauvegarde = 1;
                        }
                        break;

                    case INFORMATION:
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Bouton information", "Bouton information", NULL);
                        break;
                    }
                }
            }
        }
    }

    if(event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_MINIMIZED)
    {
        while(1)
        {
            if (SDL_WaitEvent(event))
            {
                if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
                {
                    *continuer = 0;
                    break;
                }

                if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_MAXIMIZED)
                {
                    if (!menuPause(carte, continuer, textureBouton, textureMenuPause, destinationMenuPause, textureBlack, destinationBlack, destinationBoutonsMenuPause, renderer, window, marioGenere, mode, sauvegarde))
                        retourMenu = 1;
                    break;
                }
            }
        }
    }

    SDL_FreeSurface(screenshot);

    return retourMenu;
}

int chargementMenu(SDL_Renderer *renderer, SDL_Texture *textureMenu, SDL_Rect *destinationMenu, SDL_Texture *textureFlecheMenu, SDL_Rect *destinationFlecheMenu, int option)
{
    int jouer = 1;

    if (option == 2)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    if (option)
        destinationFlecheMenu->y = destinationMenu->y + 0.537 * destinationMenu->h;
    else
        jouer = 0;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureMenu, 0, destinationMenu);
    SDL_RenderCopy(renderer, textureFlecheMenu, 0, destinationFlecheMenu);
    SDL_RenderPresent(renderer);

    return jouer;
}

int menuPause(int carte[][NB_CASES], int *continuer, SDL_Texture *textureBouton[], SDL_Texture *textureMenuPause, SDL_Rect *destinationMenuPause, SDL_Texture *textureBlack, SDL_Rect *destinationBlack, SDL_Rect destinationBouttonsMenuPause, SDL_Renderer *renderer, SDL_Window *window, int *marioGenere, int mode, int *sauvegarde)
{
    int x, y, w, h, eventX, eventY, option = 1, sauvegardeSupprimer = 0;
    SDL_Event event;

    SDL_RenderCopy(renderer, textureBlack, 0, destinationBlack);
    SDL_RenderCopy(renderer, textureMenuPause, 0, destinationMenuPause);
    SDL_RenderPresent(renderer);

    x = destinationBouttonsMenuPause.x;
    y = destinationBouttonsMenuPause.y;
    w = destinationBouttonsMenuPause.w;
    h = destinationBouttonsMenuPause.h;

    while(*continuer)
    {
        if(SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                *continuer = 0;

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                eventY = event.button.y;
                eventX = event.button.x;

                if (eventX >= x && eventX <= x+w)
                {
                    if(eventY >= y-274*h/200 && eventY <= y-274*h/200+h)
                        break;

                    if(eventY >= y && eventY <= y+h)
                    {
                        if (mode == EDITEUR)
                        {
                            option = 1;
                            reinitialiser(carte);
                        }
                        else
                            option = genererPartie(carte, renderer);

                        *marioGenere = 0;
                        sauvegardeSupprimer = 1;
                    }

                    if(eventY >= y+274*h/200 && eventY <= y+274*h/200+h)
                    {
                        option = 0;
                        sauvegardeSupprimer = 1;
                    }

                    if (sauvegardeSupprimer)
                    {
                        if (*sauvegarde)
                        {
                            *sauvegarde = 0;
                            textureBouton[SAUVEGARDE] = textureBouton[SAUVEGARDER];
                        }

                        break;
                    }
                }
            }
        }
    }

    return option;
}
