#pragma once

#include "forme.h"
#include <SFML/Graphics.hpp>
#include "tools.h"
#include "rectangle.h"
#include "Cercle.h"
#include "Polygone.h"

//Le constructeur avec paramètres
template <typename T>
Forme<T>::Forme(const sf::Vector2f &pos, T epai,const sf::Color &c_back,const sf::Color &c_bor) :position(pos),epaisseur_bordure(epai),couleur_background(c_back), couleur_bordure(c_bor)
{
    debug("Constructeur : Forme");
}

//le constructeur par copie
template<typename T>
Forme<T>::Forme(const Forme<T>& forme) : position(forme.position), epaisseur_bordure(forme.epaisseur_bordure),couleur_background(forme.couleur_background), couleur_bordure(forme.couleur_bordure)
{
    debug("Constructeur par copie : Forme");
}

//destructeur
template <typename T>
Forme<T>::~Forme()
{
    delete &couleur_background;
    delete &couleur_bordure;
    delete &position;

}

// test type
template <typename G, typename H>
bool typetest(const Forme<H>& forme){

    return !strcmp( typeid(forme).name(), typeid(G).name() );
}


//affectation par copie
template<typename T>
Forme<T>& Forme<T>::operator=(const Forme<T>& forme)
{
    debug("Affectation par copie : Forme");
    position = forme.position;
    epaisseur_bordure=forme.epaisseur_bordure;
    couleur_background=forme.couleur_background;
    couleur_bordure = forme.couleur_bordure;
    return *this;
}

template<typename T>
void Forme<T>::operator>>(const shared_ptr<sf::RenderWindow> &window)
{
    //cette methode ne doit pas etre appelée";
    cout << "Affichage de forme .." << endl;

};

template <typename T>
Forme<T>& Forme<T>::operator*(T scale)
{
    //"cette methode ne doit pas etre appelée"
    return *this;
}

template <typename T>
Forme<T>& Forme<T>::operator/(T scale)
{
    //"cette methode ne doit pas etre appelée"
    return *this;
}


template <typename T>
Forme<T>& Forme<T>::operator<<(const sf::Vector2f &vect)
{
    debug("Surcharge operateur << Vecteur");
    this->position.x = vect.x;
    this->position.y = vect.y;
    return *this;
}

template <typename T>
Forme<T>& Forme<T>::operator<<(const Couleur &couleur)
{
    debug("Surcharge operateur << Couleur");
    if (!couleur.type) this->couleur_background = couleur.col;
    else this->couleur_bordure = couleur.col;
    return *this;
}


//Distance entre deux formes
template<typename T>
T Forme<T>::operator%(const Forme<T>& forme) const
{

    T dx = pow(this->position.x - forme.position.x , 2 );
    T dy = pow(this->position.y - forme.position.y , 2 );
    return static_cast<T>( sqrt(dx + dy) );

};

template <typename T>
bool Forme<T>::operator<(Forme<T>& forme)
{
    debug("Surcharge operateur <");

    T superficie1,superficie2;

    if ( typetest<Rectangle<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

    if ( typetest<Cercle<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

    if ( typetest<Rectangle<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

     if ( typetest<Cercle<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

    if ( typetest<Polygone<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

    if ( typetest<Polygone<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

    if ( typetest<Polygone<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

     if ( typetest<Cercle<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

     if ( typetest<Rectangle<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

    return superficie1 < superficie2;
}

template <typename T>
bool Forme<T>::operator>(Forme<T>& forme)
{
    debug("Surcharge operateur >");

    T superficie1,superficie2;

    if ( typetest<Rectangle<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

    if ( typetest<Cercle<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

    if ( typetest<Rectangle<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

     if ( typetest<Cercle<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

      if ( typetest<Polygone<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

    if ( typetest<Polygone<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

    if ( typetest<Polygone<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

     if ( typetest<Cercle<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

     if ( typetest<Rectangle<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

    return superficie1 > superficie2;
}

template <typename T>
bool Forme<T>::operator==(Forme<T>& forme)
{
    debug("Surcharge operateur ==");
    T superficie1, superficie2;

    if ( typetest<Rectangle<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

    if ( typetest<Cercle<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

    if ( typetest<Rectangle<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

     if ( typetest<Cercle<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

      if ( typetest<Polygone<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

    if ( typetest<Polygone<T>>(*this) && typetest<Rectangle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<T>&>(forme)).superficie();
    }

    if ( typetest<Polygone<T>>(*this) && typetest<Cercle<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<T>&>(forme)).superficie();
    }

     if ( typetest<Cercle<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

     if ( typetest<Rectangle<T>>(*this) && typetest<Polygone<T>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<T>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<T>&>(forme)).superficie();
    }

    return superficie1 == superficie2;
}




//Augmenter la rotation
template <typename T>
Forme<T>& Forme<T>::operator+(int degre){
    if( typetest<Rectangle<T>>(*this) ){
             debug("surcharge +");
            (dynamic_cast<Rectangle<T>&>(*this).getRectangle()).rotate(degre);
    }

    if( typetest<Cercle<T>>(*this) ){
             debug("surcharge +");
            (dynamic_cast<Cercle<T>&>(*this).getCercle()).rotate(degre);
    }

    if( typetest<Polygone<T>>(*this) ){
             debug("surcharge +");
            (dynamic_cast<Polygone<T>&>(*this).getPolygone()).rotate(degre);
    }

    return *this;
}

//Diminuer la rotation
template <typename T>
Forme<T>& Forme<T>::operator-(int degre){
    if( typetest<Rectangle<T>>(*this) ){
             debug("surcharge -");
            (dynamic_cast<Rectangle<T>&>(*this).getRectangle()).rotate(360-degre);
    }

    if( typetest<Cercle<T>>(*this) ){
             debug("surcharge -");
            (dynamic_cast<Cercle<T>&>(*this).getCercle()).rotate(360-degre);
    }

    if( typetest<Polygone<T>>(*this) ){
             debug("surcharge -");
            (dynamic_cast<Polygone<T>&>(*this).getPolygone()).rotate(360-degre);
    }
    return *this;
}

//Augmenter la taille du contour
template <typename T>
Forme<T>& Forme<T>::operator++(){
    debug("surcharge ++");
    epaisseur_bordure++;
    return *this;
}
//Reduire la taille du contour
template <typename T>
Forme<T>& Forme<T>::operator--(){
    debug("surcharge --");
    epaisseur_bordure--;
    return *this;
}

//Calculer la superficie d'un rectangle
template<typename T>
T Forme<T>::superficie() const
{
    return 0;
}

//Calculer le périmètre d'un rectangle
template<typename T>
T Forme<T>::perimetre() const
{
    return 0;
}


//affichage

template<typename T>
ostream& operator<<(ostream& out, Forme<T>& forme)
{
    //bool isRECT = !strcmp( typeid(forme).name(), typeid(Rectangle<int>).name() );
    bool isRECT = typetest<Rectangle<T>>(forme);
    bool isCERCLE = typetest<Cercle<T>>(forme);
    bool isPOLYGONE = typetest<Polygone<T>>(forme);

    if ( isRECT ) out << RECTANGLE;
    if ( isCERCLE ) out << CERCLE;
    if ( isPOLYGONE ) out << POLYGONE;

    out << " , ";
    out << getNameByColor(forme.couleur_background);
    out << " , ";
    out << getNameByColor(forme.couleur_bordure);
    out << " , ";
    out << forme.epaisseur_bordure;
    out << " , ";
    out << "x = ";
    out << forme.position.x;
    out << " y = ";
    out << forme.position.y;
    out << " , ";
    // metriques
    // classe
    if ( isRECT )
    {
        out << "longueur : ";
        out << dynamic_cast<Rectangle<T>&>(forme).getLongueur();
        out << " largeur :  ";
        out << dynamic_cast<Rectangle<T>&>(forme).getLargeur();
    }
    else if ( isCERCLE )
    {
        out << "rayon : ";
        out << dynamic_cast<Cercle<T>&>(forme).getRayon();
    }
    else if ( isPOLYGONE )
    {
        out << "nb points: ";
        out << dynamic_cast<Polygone<T>&>(forme).getNbr_points();
        out << " rayon :  ";
        out << dynamic_cast<Polygone<T>&>(forme).getRayon();
    }
    out << endl;
    return out;
};
