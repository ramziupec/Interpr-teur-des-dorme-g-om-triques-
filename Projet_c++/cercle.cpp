

#pragma once
#include "Cercle.h"
#include "tools.h"

// les constructeurs
template<typename T>
Cercle<T>::Cercle(const sf::Vector2f &pos, T epai,const  sf::Color &c,const sf::Color &c_bor, T r) : Forme<T>(pos, epai, c, c_bor), rayon(r)
{
    debug("Constructeur : Cercle");
}

template<typename T>
Cercle<T>::Cercle(T x, T y,T epai,const sf::Color &c,const sf::Color &c_bor, T r) : Forme<T>(sf::Vector2f((float)x, (float)y),epai,c, c_bor), rayon(r)
{
	debug("Constructeur : Cercle");
}

//le constructeur par copie
template<typename T>
Cercle<T>::Cercle(const Cercle<T>& cer) : Forme<T>(cer), rayon(cer.rayon)
{
    debug("Constructeur de copie: Cercle");
}

//Destructeur
template<typename T>
Cercle<T>::~Cercle()
{
    delete &cercle;
}



//affectation par copie
template<typename T>
Cercle<T>& Cercle<T>::operator=(const Cercle<T> &cer)
{
    debug("Affectation par copie : Cercle");
    rayon = cer.rayon;
    (Forme<T>)(*this)=(Forme<T>)cer;
    return *this;
}

template <typename T>
Cercle<T>& Cercle<T>::operator*(T scale)
{
    this->rayon *= scale;
    cout << "surcharge *" << endl;
    return *this;
}



template <typename T>
Cercle<T>& Cercle<T>::operator/(T scale)
{
    if (scale>0)
    {
        this->rayon /= scale;
        Cercle<int> nouveau = *this;
        cout << "surcharge /" << endl;

    }
    else
    {
        throw string(SCALE_VALUE_INVALIDE);
    }
    return *this;
}


template<typename T>
void Cercle<T>::operator>>(const shared_ptr<sf::RenderWindow> &window)
{
    this->cercle.setRadius(this->rayon);
    cercle.setPosition(this->position);
    cercle.setOutlineThickness(this->epaisseur_bordure);
    cercle.setFillColor(this->couleur_background);
    cercle.setOutlineColor(this->couleur_bordure);
    window->draw(cercle);
}


//calculer la superficie d'un cercle
template<typename T>
T Cercle<T>::superficie() const
{
    return (this->rayon)*(this->rayon)*(3.14);
}

//calculer le périmètre d'un cercle
template<typename T>
T Cercle<T>::perimetre() const
{
    return (this->rayon)*(3.14);
}


//récupérer le rayon d'un cercle
template<typename T>
T Cercle<T>::getRayon() const
{
    return this->rayon;
}

//récupérer le circleShape
template<typename T>
sf::CircleShape& Cercle<T>::getCercle()
{
    return this->cercle;
}
