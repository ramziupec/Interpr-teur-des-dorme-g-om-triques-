#pragma once
#include "Polygone.h"
#include "tools.h"
#include "cmath"

template<typename T>
Polygone<T>::~Polygone()
{
    delete &polygone;
}

// Implémenter le constructeur
template<typename T>
Polygone<T>::Polygone(const sf::Vector2f &pos, T epai,const sf::Color &c,const sf::Color &c_bor, T r, unsigned int points) : Forme<T>( pos,epai, c, c_bor), rayon(r), nbr_points(points)
{
    switch (points)
	{
	case 3:
		debug("Constructeur : Polygone regulier --> Triangle");
		break;
	case 4:
		debug("Constructeur : Polygone regulier --> Carre");
		break;
	case 8:
		debug("Constructeur : Polygone regulier --> Octogone");
		break;
	default:
		debug("Constructeur : Polygone regulier");
		break;
	}
}

template<typename T>
Polygone<T>::Polygone(T x, T y, T epai,const sf::Color &c,const sf::Color &c_bor, T r, unsigned int points) : Forme<T>(sf::Vector2f((float)x, (float)y),epai, c, c_bor), rayon(r), nbr_points(points)
{
    switch (points)
	{
	case 3:
		debug("Constructeur : Polygone regulier --> Triangle");
		break;
	case 4:
		debug("Constructeur : Polygone regulier --> Carre");
		break;
	case 8:
		debug("Constructeur : Polygone regulier --> Octogone");
		break;
	default:
		debug("Constructeur : Polygone regulier");
		break;
	}
}

//le constructeur par copie
template<typename T>
Polygone<T>::Polygone(const Polygone<T>& poly) : Forme<T>(poly), rayon(poly.rayon), nbr_points(poly.nbr_points)
{
    debug("constructeur par copie: Polygone");
}




//affectation par copie
template<typename T>
Polygone<T>& Polygone<T>::operator=(const Polygone<T>& poly)
{
    debug("Affectation par copie : Polygone");
    rayon = poly.rayon;
    nbr_points= poly.nbr_points;
    (Forme<T>)(*this)=(Forme<T>)poly;
    return *this;
}



//changer la couleur d'un polygone


template <typename T>
Polygone<T>& Polygone<T>::operator*(int scale)
{
    this->rayon*= scale;
    cout << "surcharge *" << endl;
    return *this;
}


template <typename T>
Polygone<T>& Polygone<T>::operator/(int scale)
{
    if (scale>0)
    {
        this->rayon /= scale;
        Polygone<int> nouveau = *this;
        cout << "surcharge /" << endl;

    }
    else
    {
        throw string(SCALE_VALUE_INVALIDE);
    }
    return *this;
}


template<typename T>
void Polygone<T>::operator>>(const shared_ptr<sf::RenderWindow> &window)
{
    polygone.setRadius(this->rayon);
    polygone.setPointCount(this->nbr_points);
    polygone.setPosition(this->position);
    polygone.setOutlineThickness(this->epaisseur_bordure);
    polygone.setFillColor(this->couleur_background);
    polygone.setOutlineColor(this->couleur_bordure);
    window->draw(polygone);
}

//calculer la superficie d'un rectangle
template<typename T>
T Polygone<T>::superficie() const
{
  return ( (this->nbr_points/2)*(pow(this->rayon, 2))*(sin(360/this->nbr_points)) );
}

//calculer le périmètre d'un rectangle
template<typename T>
T Polygone<T>::perimetre() const
{
    return ( 2*(this->nbr_points)*(this->rayon)*(sin(180/this->nbr_points)) );
}

//récupérer le rayon d'un polygone
template<typename T>
T Polygone<T>::getRayon() const
{
    return this->rayon;
}

//récupérer le nombre de cotés d'un polygone
template<typename T>
T Polygone<T>::getNbr_points() const
{
    return this->nbr_points;
}

template<typename T>
sf::CircleShape& Polygone<T>::getPolygone()
{
    return this->polygone;
}

