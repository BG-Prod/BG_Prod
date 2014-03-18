/*
    Secrets of Universe
    Copyright (C) 2014  BG Prod

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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <fmod.h>

#include <Input.h>
#include <Image.h>
#include <Screen.h>
#include <Object.h>



#define SCREEN_REFRESH      40
#define DEBUG               std::cerr << std::endl <<
#define NOMBRE_IMAGE        7
#define NOMBRE_MUSIQUE      1
#define NOMBRE_POLICE       0


const std::string cheminRessources = "ressources/";
const std::string cheminSon = cheminRessources + "sons/";
const std::string cheminImage = cheminRessources + "images/";
const std::string cheminFile = cheminRessources + "fichiers/";
const std::string cheminPolice = cheminRessources + "polices/";
const std::string cheminData = cheminRessources + "datas/";


class Application
{
    public:
        Application();
        virtual ~Application();

        virtual void app();

        void loadImages();                          /// charge les images utiles
        void loadMusics(FMOD_SYSTEM * p_system, FMOD_SOUND ** p_sons);   /// charge les musiques utiles
        void loadFonts(TTF_Font ** p_polices);                           /// charge les polices utiles

        void freeImages();  /// lib�re les images charg�es
        void freeMusics(FMOD_SOUND ** p_sons);   /// lib�re les musiques charg�es
        void freeFonts(TTF_Font ** p_polices);   /// lib�re les polices charg�es

        static SDL_Surface* copieSurface(SDL_Surface *surf);

        void fps();      /// r�gule le temps

    protected:
        void initialisation();        /// initialise le jeu
        void fermeture();             /// ferme le jeu

        /// time
        int tempsPrecedent, tempsActuel, screen_refresh;
        /// system information
        struct tm Today;
        time_t maintenant;
        std::string nameComputeur;
        std::string nameUser;
        /// screen
        Screen * screen;
        /// ressources
        std::vector<Image*> images;
        FMOD_SYSTEM * system;
        FMOD_SOUND ** musiques;
        TTF_Font ** polices;
        /// control
        Input * in;
        /// object
        std::vector<Object*> objects;
};

#endif /// APPLICATION_H
