/** UTILITIES **/

#ifndef __TOOLS__
#define __TOOLS__

#include "constantes.h"
//pour modifier la couleur d'ecriture
void SetColor(int ForgC);
//retourne le nom de la couleur sf::Color
sf::Color getColorByName(string colorname);
// retourne le nom de la couleur
string getNameByColor(const sf::Color &);
void debug(string text);
string sizeToString(size_t sz);

#endif // __TOOLS__
