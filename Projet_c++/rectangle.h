#pragma once

#include "forme.h"

template<typename T>
class Rectangle : public Forme<T>
{
	
	protected:

    T longueur;
    T largeur;
    RectangleShape rectangle;
    
    
     public:

    /** CONSTRUCTEURS **/
    Rectangle(const sf::Vector2f &pos, T epai,const sf::Color &c,const sf::Color &c_bor, T lo, T la);
    Rectangle( T x, T y,T epai,const Color &c,const Color &c_bor, T lo, T la);
    Rectangle(const Rectangle<T>& rect);

    /** DESTRUCTEUR **/
    ~Rectangle();

    /** AFFICHAGE **/
    void operator>>(const shared_ptr<sf::RenderWindow> &window);

    /** SURCHARGE OPERATEURS **/
    Rectangle<T>& operator=(const Rectangle<T>& rect);
    Rectangle<T>& operator*(T scale);
    Rectangle<T>& operator/( T scale);


    /** METHODES **/
    T superficie() const;
    T perimetre() const;
    T getLongueur() const;
    T getLargeur() const;
    RectangleShape& getRectangle();
    friend Rectangle<T> flushRectangle(Rectangle<T> rect);

};
