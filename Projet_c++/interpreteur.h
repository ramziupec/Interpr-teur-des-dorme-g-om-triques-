#pragma once

#include "tools.h"
#include "forme.cpp"
#include "persistence.h"

template <typename C, typename E>
class Interpreteur
{
	protected:

    /** ATTRIBUTS DE LA CLASSE **/

    shared_ptr<sf::RenderWindow> window; // la Fenetre de dessin
    shared_ptr<Persistence<C,Forme<E>>> persistance; // La Persistance pour stocker les formes
    string command; // Pour lire la Commande
    istringstream isstream; // Commande transformée en flux
    string keyword; // Mot extrait de la commande
    bool endofcommand; // true = commande lue

    /** ATTRIBUTS TEMPORAIRES, SERVENT POUR LE PASSAGE DE PARAMETRES **/

    string form_id; // identifient de la forme
    string form_type; // type de la forme
    sf::Color col_f; // couleur du background de la forme
    sf::Color col_b; // couleur de la bordure
    int epai; // epaisseur de la bordure
    int x; // position x
    int y; // position y
    int m1; // metrique 1
    int m2;// metrique 2

  public:

     /** CONSTRUCTEURS **/
    Interpreteur(const shared_ptr<sf::RenderWindow> &window,const shared_ptr<Persistence<C,Forme<E>>> &persistance);

    /** DESTRUCTEUR **/
    ~Interpreteur();

    /* Lire la commande **/
    void lire();

    /* Executer la commande */
    void executer();

  private :

    /* Interpreter et retourner un mot de la commande */
    string interpreter();

    /* Interpreter et retourner un mot de la commande entier */
    int interpreterint();

    /* Lire une commande de creation d'objet */
    void parse();

    /* Commande HELP */
    void help();

    /* Signaler la fin d'une commande au controle d'execution */
    void terminateCommand();

};
