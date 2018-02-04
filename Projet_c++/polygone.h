#pragma once
#include "forme.h"

template<typename T>
class Polygone : public Forme<T>
{
	
	/** Arguments **/
    T rayon;
	unsigned int nbr_points;
    CircleShape polygone;
    
	public:

    /** CONSTRUCTEURS **/
    Polygone(const sf::Vector2f &pos, T epai,const sf::Color &c,const sf::Color &c_bor, T r, unsigned int points);
    Polygone( T x, T y,T epai,const sf::Color &c,const sf::Color &c_bor, T r, unsigned int points);
    Polygone(const Polygone<T> &polygone);

    /** DESTRUCTEUR **/
    ~Polygone();

    /** AFFICHAGE **/
    void operator>>(const shared_ptr<sf::RenderWindow> &window);

    /** SURCHARGE OPERATEURS **/
    Polygone<T>& operator=(const Polygone<T> &polygone);
    Polygone<T>& operator*(int scale);
    Polygone<T>& operator/(int scale);

    /** METHODES **/
    T superficie() const;
    T perimetre() const;
    T getRayon() const;
    T getNbr_points() const;
    CircleShape& getPolygone() ;

    friend Polygone<T> flushPolygone(Polygone<T> polygone);
};

