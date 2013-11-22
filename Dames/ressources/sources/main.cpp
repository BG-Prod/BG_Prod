/*
    Draughts - Les Dames
    Copyright (C) 2013  Gar�on Beno�t

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact me : benoit.garconbesson@gmail.com
*/

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <SDL_getenv.h>
#include <FMOD/fmod.h>


#include "Texte.h"
#include "utile.h"
#include "affichage.h"
#include "verifier_deplacement.h"
#include "jeu.h"



int main ( int argc, char** argv )
{
/// initialisation son & image
    /// initialisation FMOD
    FMOD_SYSTEM * system;
    FMOD_System_Create(&system);
    /// initialisation image & son
    initialisation(system);


/// d�claration et chargements des ressources
    /// create a new window
    putenv("SDL_VIDEO_WINDOW_POS=center"); /// pour centrer la fen�tre
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    /// images
    SDL_Surface** images = NULL;
    images = (SDL_Surface **) malloc (sizeof(SDL_Surface*) * NOMBRE_IMAGE);
    load_images(images);
    /// sons
    FMOD_SOUND ** musiques = NULL;
    musiques = (FMOD_SOUND **) malloc (sizeof(FMOD_SOUND*) * NOMBRE_MUSIQUE);
    load_musiques(system, musiques);
    /// polices
    TTF_Font ** polices = NULL;
    polices = (TTF_Font **) malloc(sizeof(TTF_Font*) * NOMBRE_POLICE);
    load_polices(polices);


/// Icone
    SDL_WM_SetIcon(images[0], NULL);

/// titre
    SDL_WM_SetCaption("Dames", NULL);


/// program main loop
    Input in;
    memset(&in,0,sizeof(in));
    int tempsPrecedent = 0, tempsActuel = 0;

    int * menu = new int;
    *menu = -1;

    SDL_Rect place = {LARGEUR_ECRAN/2 - images[0]->w/2,HAUTEUR_ECRAN/2 - images[0]->h/2,0,0};

///on joue la musique de fond
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[0], 0, NULL);

    while(!in.key[SDLK_ESCAPE] && !in.quit)         /// boucle principale
    {
        /// mise � jour des events
        updateEvents(&in);


        /// gestion du frame
        tempsActuel = SDL_GetTicks();

        if(tempsActuel - tempsPrecedent >= SCREEN_REFRESH)
        {
            tempsPrecedent = tempsActuel;
        }
        else if (tempsActuel - tempsPrecedent < SCREEN_REFRESH)
        {
            SDL_Delay(tempsActuel - tempsPrecedent);
            tempsPrecedent = tempsActuel;
        }



        /// resize taille �cran
        if(in.key[SDLK_F1]) /// fullscreen
        {
            SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
        }
        if(in.key[SDLK_F2]) /// reduce size
        {
            SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
        }





        if(*menu == 1 || in.key[SDLK_RETURN]) /// jouer
        {
            game(&in, images);
        }

        if(*menu == -9) /// quitter le jeu
        {
            in.quit = 1;
        }

        if(*menu == -1)
        {
            SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
            SDL_BlitSurface(images[0], NULL, SDL_GetVideoSurface(), &place);
        }

        SDL_Flip(SDL_GetVideoSurface());
    }/// end main loop


/// nettoyage
    /// free pointeurs
    delete menu;
    /// free loaded bitmap and created surface
    SDL_FreeSurface(screen);
    free_images(images);
    free_polices(polices);
    /// lib�ration des sons
    free_musiques(musiques);
    /// fermeture propre de ce qui est ouvert dans initialisation()
    fermeture(system);


/// all is well ;)
    printf("Exited cleanly\n");
    return 0;
}



/// REMARQUES

/// 22/11/2013 : mise en place du texte et correction de la prise interdite par les joueurs
/// 31/10/2013 : tour par tour + interface graphique + texte
/// 08/10/2013 : m�j mouvements des dames + fin de partie
/// 08/10/2013 : jeu marche pour hauteur = 768 et 1080 + d�but de test des mouvements
/// 05/10/2013 : d�placement de pi�ces op�rationnel
/// 01/10/2013 : affichage mis en place + impl�mentation partie m�canique (d�placement pi�ces)
/// 30/09/2013 : structure mise en place
/// 28/09/2013 : cr�ation du jeu



