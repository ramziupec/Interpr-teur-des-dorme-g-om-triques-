#pragma once

#include "constantes.h"

/** TEMPLATE DE CLASSE **/
template <typename C, typename V>
class Persistence;

/** SURCHARGE DE std::cout << Persistance **/
template <typename C, typename V>
ostream& operator<<(ostream& os, const shared_ptr<Persistence<C,V>>& persist);

template <typename C, typename V>
class Persistence
{
protected:

    /* Utilisation de la classe std::map */
    map<C,shared_ptr<V>> data;

public :

    /** DESTRUCTEUR **/
    ~Persistence();

  /** SURCHARGE OPERATEURS **/

  /* inserer un couple clé-valeur */
    void operator()(const C &cle, const shared_ptr<V> &valeur,const shared_ptr<sf::RenderWindow> &window);


    /* atteindre un element via une clé */
    shared_ptr<V>& operator[](const C &cle);

    /* Afficher tout les objets de la persistance sur Window */
    void operator>>(const shared_ptr<sf::RenderWindow> &window) const;

    /** AFFICHAGE sur console **/
    friend ostream& operator<< <>(ostream& os, const shared_ptr<Persistence>& persist);

    /* Voir si un element existe, selon la clé */
    int existe(const C &cle);

    /** METHODES **/

    /* Supprimer un element */
    void supprimer(const C &cle,const shared_ptr<sf::RenderWindow>& window);

};

