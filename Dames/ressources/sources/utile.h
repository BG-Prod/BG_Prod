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

#ifndef UTILE_H_INCLUDED
#define UTILE_H_INCLUDED



#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <FMOD/fmod.h>



#define CX_SCREEN           GetSystemMetrics(SM_CXSCREEN)            ///Largeur
#define CY_SCREEN           GetSystemMetrics(SM_CYSCREEN)            ///Hauteur
#define NB_CARRE_X          10
#define NB_CARRE_Y          10
#define TAILLE_CARRE        HAUTEUR_ECRAN / 10
#define LARGEUR_ECRAN       CX_SCREEN                   ///     800     ///  1366    ///  1920
#define HAUTEUR_ECRAN       size_of_game(CY_SCREEN)     ///     600     ///  768     ///  1080
#define SCREEN_REFRESH      40
#define DEBUG               std::cerr << std::endl <<
#define NOMBRE_IMAGE        11
#define NOMBRE_MUSIQUE      1
#define NOMBRE_POLICE       1



const std::string cheminRessources = "ressources/";
const std::string cheminSon = cheminRessources + "sons/";
const std::string cheminImage = cheminRessources + "images/";
const std::string cheminFile = cheminRessources + "fichiers/";
const std::string cheminPolice = cheminRessources + "polices/";



struct Input    /// structure pour la capture des �v�nements
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
    char quit;
};



void updateEvents(Input *);             /// M�J des �v�nements

void initialisation(FMOD_SYSTEM * p_system);        /// initialise le jeu
void fermeture(FMOD_SYSTEM * p_system);             /// ferme le jeu

void load_images(SDL_Surface ** p_images);                          /// charge les images utiles
void load_musiques(FMOD_SYSTEM * p_system, FMOD_SOUND ** p_sons);   /// charge les musiques utiles
void load_polices(TTF_Font ** p_polices);                           /// charge les polices utiles

void free_images(SDL_Surface ** p_images);  /// lib�re les images charg�es
void free_musiques(FMOD_SOUND ** p_sons);   /// lib�re les musiques charg�es
void free_polices(TTF_Font ** p_polices);   /// lib�re les polices charg�es

int size_of_game(int p_hauteur_ecran);        /// d�termine la hauteur de l'�cran

int nombreLignes (const std::string & filename);
// attention la ligne suivante renvoie la ligne 1 si on demande la 0
std::string niemeLigne(const std::string & filename, int p_count);

SDL_Surface* copieSurface(SDL_Surface *surf);


#endif /// UTILE_H_INCLUDED
