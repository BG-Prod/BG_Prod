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
#include "verifier_deplacement.h"
#include "affichage.h"


void game(Input * p_in, SDL_Surface ** p_images);   /// g�re une partie enti�re
void jouer_jeu(Input * p_in, bool * p_can_play, int ** p_tableau, int * p_pion, int * p_origine_X, int * p_origine_Y, int * p_destination_X, int * p_destination_Y);    /// g�re la partie algo
void time_to_IA();                                  /// g�re le comportement de l'IA et si elle peut jouer
void tester_action();                               /// test une action
bool tester_mouvement(int ** p_tableau,                 /// un tableau 10*10 contenant la valeur des pi�ces
                      int p_piece,                      /// valeur de le pi�ce qui effectue le mouvement
                      int p_origin_X, int p_origin_Y,   /// origine de la pi�ce dans le tableau
                      int p_dest_X, int p_dest_Y);      /// destination souhait�e dans le tableau

void pion_to_dame(int ** p_tableau);

/// g�re les d�placements de pi�ces
void cliquer_prendre_poser(Input * p_in, int ** p_tableau, int * p_pion,
                           int * p_origine_X, int * p_origine_Y,
                           int * p_destination_X, int * p_destination_Y);
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
