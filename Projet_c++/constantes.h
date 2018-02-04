#pragma once

/*****************************/
/*** INCLUDES **************/
/*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <map>
#include <dos.h>
#include <dir.h>
#include <thread>
#include <typeinfo>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include "couleur.h"

/*****************************/
/*** NAMESPACE **************/
/*****************************/

using namespace std;
using namespace sf;

/*****************************/
/*** CONFIG ******************/
/*****************************/

#define DEBUG 1 // Activer pour afficher les details des operations

#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_SIZE_X 600
#define WINDOW_SIZE_Y 600
#define MAX_FORM_METER 200
#define MAX_FORM_BORD_SIZE 5
#define MAX_FORM_STORAGE 5
#define FRAME_RATE_LIMIT 60

/*****************************/
/*** COMMANDES **************/
/*****************************/

#define CREATE "create"
#define UNSELECT "unselect"
#define CHANGE_COLOR "color"
#define MOVE "move"
#define ROTATE "rotate"
#define SCALEUP "scaleup"
#define SCALEDOWN "scaledown"
#define REMOVE "remove"
#define CLEAR "removeall"
#define CLS "cls"
#define COPY "duplicate"
#define DIST "dist"
#define COLOR "color"
#define LIST "list"
#define HELP "help"
#define TEST "test"
#define ROTATE "rotate"
#define CONTOUR "contour"
#define SUPERFICIE "superficie"
#define PERIMETRE "perimetre"
#define EXIT "exit"

/*****************************/
/*** MOTS CLES **************/
/*****************************/

#define SUPERIEUR ">"
#define INFERIEUR "<"
#define EGALE "=="
#define TRUE "vrai"
#define FALSE "faux"
#define CONTOUR "contour"
#define BACKGROUND "background"
#define PLUS_PLUS "++"
#define MOINS_MOINS "--"
#define PLUS "+"
#define MOINS "-"

/*****************************/
/*** CAS DE TEST **************/
/*****************************/

#define TEST_RECTANGLE "testrect"
#define TEST_CERCLE "testcercle"
#define TEST_POLYGONE "testpolygone"
#define TESTCASE "testcase"

/*****************************/
/*** FORMES ******************/
/*****************************/

#define RECTANGLE "rectangle"
#define POLYGONE "polygone"
#define CERCLE "cercle"

/*****************************/
/*** COULEURS ******************/
/*****************************/

#define ROUGE "rouge"
#define VERT "vert"
#define BLEU "bleu"
#define NOIR "noir"
#define BLANC "blanc"
#define JAUNE "jaune"

/*****************************/
/*** MESSAGES 1 ******************/
/*****************************/

#define START_MSG "MINI PROJET EN C++ Dessin des formes"
#define START_MSG_1 "DEMANDE PAR: Mr.LUIDNEL MAIGNAN"
#define START_MSG_2 ""
#define START_MSG_3 "UNIVERSITE : UPEC "
#define START_MSG_5 "FILIERE : MASTER 2 LOGICIEL"
#define START_MSG_4 "-----------------------------------------------"
#define EXIT_CMD_MSG "Au revoir !"

#define COMMANDE_INCONNUE "Commande inconnue : "
#define COULEUR_INCONNUE "Couleur inconnue : "
#define FORME_INCONNUE "Forme inconnue : "
#define PARAMETRE_MANQUANT "Commande incomplete : tapez help pour afficher l'aide"
#define NOMBRE_INVALIDE "Nombre invalide !"
#define UNKNOWN_OPERATOR "Operateur inconnu : "
#define SUPERFLUX_CHAIN "Litteraux superflux a la commande : "

/*****************************/
/*** MESSAGES 2 ******************/
/*****************************/

#define AUCUNE_FORME_SELECTIONNE "nil"
#define MSG_ALREADY_EXISTS "Cette forme existe deja"
#define MSG_NOT_EXISTS "Forme inexistante : "
#define MAX_FORM_MSG "ERREUR : Le nombre maximal de formes est atteint, pensez a supprimer !"
#define MAX_BORD_SIZE_MSG "ERREUR : L'epaisseur de la bordure doit etre inférieure ou egale a " //MAX_FORM_BORD_SIZE
#define WINDOW_OVERFLOW_ORIGIN "ERREUR : L'origine de la forme est a l'exterieur de l'ecran"
#define LONGUEUR_INF_LARGEUR "La longueur doit etre superieure a la largeur"
#define SCALE_VALUE_INVALIDE "argument invalide, la valeur doit etre superieure a 0"
#define NO_CONTOUR_BACKGROUNG_ARG "Le second argument doit avoir les valeurs "
#define SYSTEM_ERROR "Erreur système irrecuperable"
#define NOT_A_POLYGON "Un polygone doit aoir au moins 3 sommets"
