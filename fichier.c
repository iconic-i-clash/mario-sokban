#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "constantes.h"


void messageErreurFichier(char *title, char *message, int* buttonId)
{
    SDL_MessageBoxButtonData buttons[] = {
        {0, 0, "Non"},
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Oui"}
    };

    SDL_MessageBoxColorScheme colorScheme = {
        {
            {210, 210, 210},
            {0, 0, 0},
            {130, 130, 130},
            {210, 210, 210},
            {210, 210, 210}
        }
    };

    SDL_MessageBoxData messageBoxData = {
        SDL_MESSAGEBOX_ERROR,
        NULL,
        title,
        message,
        SDL_arraysize(buttons),
        buttons,
        &colorScheme
    };

    SDL_ShowMessageBox(&messageBoxData, buttonId);
}

int genererPartie(int carte[][NB_CASES], SDL_Renderer *renderer)
{
    FILE* fichier = NULL;
    int erreurFichier, butonId, i, j;
    char caractereActuel, fichierInitial[] = "111111111111111130111111111111\n111000111111111100111111111111\n111040000000000001111111111111\n111001111111111001111111111111\n111001111111111000000111111111\n111000002111111001100110001111\n111000000011111111001100401111\n111111110000000011100000001111\n111111110000000011100111111111\n111111110011110011111111111111\n111111110011110011111111111111\n111111110011110000000001111111\n111111110011110000000001111111\n111120000000011111111121111111\n111111110004011111111111111111\n111111111100011111111111111111";

    fichier = fopen(".lvl", "r");

    erreurFichier = 0;
    if(fichier != NULL)
    {
        i = 0;
        j = 0;
        do{
            caractereActuel = fgetc(fichier);

            if (caractereActuel != EOF)
            {
                if (caractereActuel == '\n')
                {
                    i++;
                    if (j != NB_CASES)
                        erreurFichier = 1;

                    j = 0;
                }
                else
                {
                    carte[i][j] = caractereActuel - 48;
                    j++;
                }
            }
        }while (caractereActuel != EOF && !erreurFichier);

        if (i+1 != LIGNES)
            erreurFichier = 1;

        fclose(fichier);
    }
    else
        erreurFichier = 1;

    if (erreurFichier)
        traiterErreurFichier(&butonId, ".lvl", fichierInitial);

    return erreurFichier;
}

void traiterErreurFichier(int *butonId, char *nomFichier, char *fichierInitial)
{
    FILE* fichier = NULL;

    messageErreurFichier("Erreur de chargement", "Une erreur est survenue lors du chargement du fichier de niveau.\nRestaurer le fichier ?", butonId);
    if(*butonId)
    {
        fichier = fopen(nomFichier, "w");

        if(fichier != NULL)
        {
            fprintf(fichier, "%s", fichierInitial);
            fclose(fichier);
        }
        else
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur de chargement", "Impossible de restaurer le fichier de niveau.", NULL);
    }
}
