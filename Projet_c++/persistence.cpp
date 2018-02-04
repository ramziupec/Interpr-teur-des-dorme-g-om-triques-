#pragma once

#include "persistence.h"
#include "tools.h"

template <typename C, typename V>
Persistence<C,V>::~Persistence() {

}

template <typename C, typename V>
int Persistence<C,V>::existe(const C &cle)
{
    return (data.count(cle)>0);
}


template <typename C, typename V>
void Persistence<C,V>::operator()(const C &cle, const shared_ptr<V> &valeur, const shared_ptr<sf::RenderWindow> &window)
{

    if (data.size() + 1 >= MAX_FORM_STORAGE )
    {
        throw string(MAX_FORM_MSG);
    }
    else if (existe(cle))
    {
        throw string(MSG_ALREADY_EXISTS);
    }
    data.insert(pair<C,shared_ptr<V>>(cle,valeur));
    *this >> window;

}

template <typename C, typename V>
shared_ptr<V>& Persistence<C,V>::operator[](const C &cle)
{

    if ( existe(cle) == 0 )
    {
        throw string(MSG_NOT_EXISTS) + string(cle);
    }
    return data[cle];

}


template <typename C, typename V>
void Persistence<C,V>::operator>>(const shared_ptr<sf::RenderWindow> &window) const
{
    window->clear();
    typedef typename std::map<C,shared_ptr<V>>::const_iterator MapIter;
    for (MapIter it=data.begin(); it!=data.end(); ++it)
    {
        auto elem = it->second;
        *elem >> window;
    }
    window->display();
}

template <typename C, typename V>
void Persistence<C,V>::supprimer(const C &cle,const shared_ptr<sf::RenderWindow>& window)
{
    data.erase(cle);
    *this >> window;
}



template <typename C, typename V>
ostream& operator<<(ostream& os, const shared_ptr<Persistence<C,V>>& persist)
{
    debug("surcharge <<");
    typedef typename std::map<C,shared_ptr<V>>::const_iterator MapIter;
    os << "------------------------------------------------------------------------------------" << endl;
    os << "FORME_ID :: FORME_TYPE, COUL_FOND, COUl_BORDURE, EPAI_BORD, POSITION, METRIQUE(S)" << endl;
    os << "------------------------------------------------------------------------------------" << endl;
    for (MapIter it=persist->data.begin(); it!=persist->data.end(); ++it)
    {
        // afficher l'id
        os << it->first;
        os << " :: ";
        os << *(it->second);
    }
    os << "------------------------------------------------------------------------------------" << endl;
    os << " ";
    os << persist->data.size();
    os << " element(s)" << endl;
    os << "------------------------------------------------------------------------------------" << endl;
    return os;
}
