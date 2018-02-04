#pragma once
#include "constantes.h"

struct Couleur
{

public :

    /** Constructeurs **/
    Couleur (sf::Color col, bool type);

    /** Destructeur **/
    ~Couleur(){
	};

    /** Attributs **/
    sf::Color col;  // Couleur
    bool type;      // Signifie le type de la couleur :: true=background , false=contour

};
