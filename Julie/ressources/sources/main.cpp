/*
    Julie
    Copyright (C) 2013  BG Prod

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

    Contact me : bgprod@outlook.com
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
#include <ctime>


#include "sqlite3.h"
#include "Input.h"
#include "BDD.h"
#include "Texte.h"
#include "utile.h"
#include "Jeu.h"


int main ( int argc, char** argv )
{
/// initialisation son & image
    /// initialisation FMOD
    FMOD_SYSTEM * system;
    FMOD_System_Create(&system);
    /// initialisation image & son
    initialisation(system);

/// verification de la date
    struct tm Today;
	time_t maintenant;

	time(&maintenant);
	Today = *localtime(&maintenant);

	Today.tm_year += 1900;
	Today.tm_mon += 1;
	Today.tm_mday;

/// username
    DWORD StrLen = 256;
    TCHAR SysInfoStr[256];
    GetComputerName(SysInfoStr, &StrLen);
    std::string nameComputeur = SysInfoStr;
    GetUserName(SysInfoStr, &StrLen);
    std::string nameUser = SysInfoStr;


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
    images = (SDL_Surface **) malloc (sizeof(SDL_Surface*)*NOMBRE_IMAGE);
    load_images(images);
    /// sons
    FMOD_SOUND ** musiques = NULL;
    musiques = (FMOD_SOUND **) malloc (sizeof(FMOD_SOUND*)*NOMBRE_MUSIQUE);
    load_musiques(system, musiques);
    /// polices
    TTF_Font ** polices = NULL;
    polices = (TTF_Font **) malloc(sizeof(TTF_Font*) * NOMBRE_POLICE);
    load_polices(polices);


/// Icone
    SDL_WM_SetIcon(images[0], NULL);

/// titre
    SDL_WM_SetCaption("Julie", NULL);

/// program main loop
    Input * in = new Input;
    int tempsPrecedent = 0, tempsActuel = 0;

    int ghost = 255;
    bool devient_ghost = true;

    int * menu = new int;
    *menu = -1;

    SDL_Rect place = {LARGEUR_ECRAN/2 - images[0]->w/2,HAUTEUR_ECRAN/2 - images[0]->h/2,0,0};

/// musiques
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[0], 0, NULL);

/// affichage du logo
    int i = 0;
    while(i<256)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
        place = {LARGEUR_ECRAN/2 - images[0]->w/2,HAUTEUR_ECRAN/2 - images[0]->h/2,0,0};
        SDL_SetAlpha(images[0], SDL_SRCALPHA, i);
        SDL_BlitSurface(images[0], NULL, SDL_GetVideoSurface(), &place);
        i++;
        SDL_Flip(SDL_GetVideoSurface());
    }

    while(i>=0)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
        place = {LARGEUR_ECRAN/2 - images[0]->w/2,HAUTEUR_ECRAN/2 - images[0]->h/2,0,0};
        SDL_SetAlpha(images[0], SDL_SRCALPHA, i);
        SDL_BlitSurface(images[0], NULL, SDL_GetVideoSurface(), &place);
        i--;
        SDL_Flip(SDL_GetVideoSurface());
    }


    place = {LARGEUR_ECRAN/2 - images[1]->w/2,HAUTEUR_ECRAN/2 - images[1]->h/2,0,0};


    while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit())  /// boucle principale
    {
        /// mise � jour des events
        in->update();

        /// gestion du frame
        fps(&tempsPrecedent, &tempsActuel, SCREEN_REFRESH);

        /// resize taille �cran
        resize_screen(*in);

        if(*menu == 1 || in->get_touche(SDLK_1) || in->get_touche(SDLK_KP1)) /// jouer
        {
            in->set_touche(SDLK_1, 0);
            in->set_touche(SDLK_KP1, 0);
            Jeu * party = new Jeu(images);
            party->game();
            delete party;
            in->set_touche(SDLK_ESCAPE, 0);
        }

        if(*menu == 2 || in->get_touche(SDLK_2) || in->get_touche(SDLK_KP2)) /// jouer
        {
            in->set_touche(SDLK_2, 0);
            in->set_touche(SDLK_KP2, 0);
            Jeu * party = new Jeu(images);
            party->conjugaison();
            delete party;
            in->set_touche(SDLK_ESCAPE, 0);
        }

        if(*menu == -9) /// quitter le jeu
        {
            in->set_exit(1);
        }

        if(*menu == -1)
        {
            SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
            place = {LARGEUR_ECRAN/2 - images[1]->w/2,HAUTEUR_ECRAN/2 - images[1]->h/2,0,0};
            SDL_BlitSurface(images[1], NULL, SDL_GetVideoSurface(), &place);
/*
            if(devient_ghost)
            {
                ghost -= 8;
            }
            else
            {
                ghost += 8;
            }
            if(ghost >= 255 || ghost <= 88)
            {
                devient_ghost = !devient_ghost;
            }
            place = {LARGEUR_ECRAN/2 - images[2]->w/2,3*HAUTEUR_ECRAN/4 - images[2]->h/2,0,0};
            SDL_SetAlpha(images[2], SDL_SRCALPHA, ghost);
            SDL_BlitSurface(images[2], NULL, SDL_GetVideoSurface(), &place);
*/
            Texte menu1;
            Texte menu2;
            menu1.print("1 - Math�matiques", "arial", 60, {255,255,255}, SDL_GetVideoSurface()->w/3, 3*SDL_GetVideoSurface()->h/4);
            menu2.print("2 - Conjugaison", "arial", 60, {255,255,255}, SDL_GetVideoSurface()->w/3, 3*SDL_GetVideoSurface()->h/4+100);
        }

        SDL_Flip(screen);
    }/// end main loop


/// nettoyage
    /// free pointeurs
    delete menu;
    delete in;
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

// 03/12/2013 : cr�ation du jeu



