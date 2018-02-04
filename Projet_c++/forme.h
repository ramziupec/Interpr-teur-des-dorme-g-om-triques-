#pragma once

#include "constantes.h"

/** Template de classe  **/
template <typename T>
class Forme;

/** SURCHARGE DE std::cout << Forme **/
template <typename T>
ostream& operator<<(ostream& out, Forme<T>& forme);

template <typename T>
class Forme
{
   protected:
     /** Arguments **/
      sf::Vector2f position;
      T epaisseur_bordure;
      sf::Color couleur_background;
      sf::Color couleur_bordure;


   public:
    /** CONSTRUCTEURS **/

    // Constructeur avec parametres
    Forme(const sf::Vector2f &pos, T epai,const sf::Color &c_back,const sf::Color &c_bor);

    // Constructeur par copie
    Forme(const Forme<T>& forme);

    /** Destructeur **/
    // Destrcuteur virtual pour autoriser l'appel des methodes des classes filles
    virtual ~Forme();

    /** Surcharge d'opérateurs **/

	// Affectation par copie
    Forme<T>& operator=(const Forme<T>& forme);

    // Afficher les details de la forme sur console
    friend ostream& operator<< <>(ostream& out, Forme& forme);

    // Afficher la forme sur fenetre
    virtual void operator>>(const shared_ptr<sf::RenderWindow> &window);

    // Augmenter la taille de la forme
    virtual Forme<T>& operator*(T scale);

    // Diminuer la taille de la forme
    virtual Forme<T>& operator/(T scale);

    //  Changer la position de la forme
    Forme<T>& operator<<(const sf::Vector2f &vect);

    // Changer les couleurs soit du background ou de bordure
    Forme<T>& operator<<(const Couleur &couleur);

    // distance entre deux formes
    T operator%(const Forme<T>& forme) const;

    // comparer la superficie de deux formes
    bool operator<(Forme<T>& forme);
    bool operator>(Forme<T>& forme);
    bool operator==(Forme<T>& forme);

    // Changer la rotation de la forme
    Forme<T>& operator+(int degre);
    Forme<T>& operator-(int degre);

    // changement de la taille du contour
    Forme<T>& operator++();
    Forme<T>& operator--();

    /** METHODES **/

    virtual T superficie() const;
    virtual T perimetre() const;

    /** TEST TYPE  : Template de fonction **/

    // tester si 'forme' est de type G<H>
    template <typename G, typename H>
    friend bool typetest(const Forme& forme);

};
