#pragma once
#include "rectangle.h"
#include "tools.h"

template<typename T>
Rectangle<T>::~Rectangle()
{
    delete &rectangle;
}

// Implémenter le constructeur
template<typename T>
Rectangle<T>::Rectangle(const sf::Vector2f &pos, T epai,const sf::Color &c,const sf::Color &c_bor, T lo, T la) : Forme<T>(pos,epai, c,c_bor), longueur(lo), largeur(la)
{
    debug("Constructeur : Rectangle");
}

template<typename T>
Rectangle<T>::Rectangle(T x, T y, T epai,const sf::Color &c,const sf::Color &c_bor, T lo, T la) : Forme<T>(sf::Vector2f((float)x, (float)y),epai,c, c_bor), longueur(lo), largeur(la)
{
    debug("Constructeur : Rectangle");
}

//le constructeur par copie
template<typename T>
Rectangle<T>::Rectangle(const Rectangle<T>& rect) : Forme<T>(rect), longueur(rect.longueur), largeur(rect.largeur)
{
    debug("Constructeur par copie: Rectangle");
}



//affectation par copie

template<typename T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& rect)
{
    debug("Affectation par copie : Rectangle");
    longueur = rect.longueur;
    largeur = rect.largeur;
    (Forme<T>)(*this)=(Forme<T>)rect;
    return *this;
}


template <typename T>
Rectangle<T>& Rectangle<T>::operator*(T scale)
{
    this->longueur *= scale;
    this->largeur *= scale;
    cout << "surcharge *" << endl;
    return *this;
}
template <typename T>
Rectangle<T>& Rectangle<T>::operator/(T scale)
{
    if (scale>0)
    {
        this->longueur /= scale;
        this->largeur /= scale;
        Rectangle<int> nouveau = *this;
        cout << "surcharge /" << endl;

    }
    else
    {
        throw string(SCALE_VALUE_INVALIDE);
    }
    return *this;
}

template<typename T>
void Rectangle<T>::operator>>(const shared_ptr<sf::RenderWindow> &window)
{

    this->rectangle.setSize(sf::Vector2f(this->longueur, this->largeur));
    rectangle.setOutlineThickness(this->epaisseur_bordure);
    rectangle.setPosition(this->position);
    rectangle.setFillColor(this->couleur_background);
    rectangle.setOutlineColor(this->couleur_bordure);
    window->draw(rectangle);
}


//calculer la superficie d'un rectangle
template<typename T>
T Rectangle<T>::superficie() const
{
    return (this->longueur)*(this->largeur);
}

//calculer le périmètre d'un rectangle
template<typename T>
T Rectangle<T>::perimetre() const
{
    return (longueur+largeur)*2;
}

//calculer la superficie d'un rectangle
template<typename T>
T Rectangle<T>::getLongueur() const
{
    return longueur;
}

//calculer le périmètre d'un rectangle
template<typename T>
T Rectangle<T>::getLargeur() const
{
    return largeur;
}

template<typename T>
sf::RectangleShape& Rectangle<T>::getRectangle()
{
    return this->rectangle;
}

