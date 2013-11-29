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

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED



#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <FMOD/fmod.h>


#include "utile.h"
#include "Texte.h"
#include "verifier_deplacement.h"
#include "affichage.h"
#include "intell.h"


void game(Input * p_in, SDL_Surface ** p_images);       /// g�re une partie enti�re
void jouer_jeu(Input * p_in, Texte * p_page, bool * p_can_play, int * p_nb_jouer, int ** p_tableau, int * p_pion, int * p_origine_X, int * p_origine_Y, int * p_destination_X, int * p_destination_Y, int *, int *);    /// g�re la partie algo
void time_to_IA(Input * p_in, bool * p_playa_turn, int * p_nb_jouer, int ** p_tableau, int * p_pion, int * p_origine_X, int * p_origine_Y, int * p_destination_X, int * p_destination_Y, int*, int*); /// g�re le comportement de l'IA et si elle peut jouer
void tester_action();                                   /// test une action
bool tester_mouvement(int ** p_tableau,                 /// un tableau 10*10 contenant la valeur des pi�ces
                      bool * p_playa_turn,
                      int p_piece,                      /// valeur de le pi�ce qui effectue le mouvement
                      int p_origin_X, int p_origin_Y,   /// origine de la pi�ce dans le tableau
                      int p_dest_X, int p_dest_Y);      /// destination souhait�e dans le tableau
bool tester_fin(int ** p_tableau, int p_pion);          /// d�termine si la partie est finie

void pion_to_dame(int ** p_tableau);

/// g�re les d�placements de pi�ces
void cliquer_prendre_poser(Input * p_in, bool * p_playa_turn, int * p_nb_jouer, int ** p_tableau, int * p_pion,
                           int * p_origine_X, int * p_origine_Y,
                           int * p_destination_X, int * p_destination_Y,
                           int * p_prise_X, int * p_prise_Y);
/// g�re les prises de pi�ces
void prendre_piece(int ** p_tableau, int p_depart_X, int p_depart_Y,
                   int * p_pion, int * p_temp_X, int * p_temp_Y);
/// g�re les poses de pi�ces
void poser_piece(int ** p_tableau, int p_arrivee_X, int p_arrivee_Y,
                   int * p_pion, int * p_temp_X, int * p_temp_Y);
/// nettoie les variables de d�placement
void nettoyer_deplacement(int * p_pion, int * p_origine_X, int * p_origine_Y,
                          int * p_destination_X, int * p_destination_Y);



#endif /// JEU_H_INCLUDED
