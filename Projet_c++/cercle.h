#pragma once

#include "forme.h"

template<typename T>
class Cercle : public Forme<T>
{

    T rayon;
    CircleShape cercle;
    
    public:

    /** CONSTRUCTEURS **/
    Cercle(const sf::Vector2f &pos, T epai,const sf::Color &c,const  sf::Color &c_bor, T r);
    Cercle( T x, T y, T epai,const sf::Color &c,const sf::Color &c_bor, T r);
    Cercle(const Cercle<T> &cer);

    /** DESTRUCTEUR **/
    ~Cercle();

    /** AFFICHAGE **/
    void operator>>(const shared_ptr<sf::RenderWindow> &window);

    /** SURCHARGE OPERATEURS **/

    Cercle<T>& operator=(const Cercle<T> &cer);
    Cercle<T>& operator*(T scale);
    Cercle<T>& operator/(T scale);

    /** METHODES **/

    T superficie() const;
    T perimetre() const;
    T getRayon() const;
    CircleShape& getCercle();

};

