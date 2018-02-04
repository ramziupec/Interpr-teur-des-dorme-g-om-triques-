/** UTILITIES **/

#include "tools.h"
#include "constantes.h"
#include "windows.h"


constexpr unsigned int hashed(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (hashed(str, h+1) * 33) ^ str[h];
}

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

Color getColorByName(string colorname)
{
    switch ( hashed(colorname.c_str()) )
    {
    case hashed(ROUGE) :
        return Color::Red;
    case hashed(VERT) :
        return Color::Green;
    case hashed(BLEU) :
        return Color::Blue;
    case hashed(NOIR) :
        return Color::Black;
    case hashed(BLANC) :
        return Color::White;
    case hashed(JAUNE) :
        return Color::Yellow;
    default :
        throw string(COULEUR_INCONNUE);
    }
}

string getNameByColor(const sf::Color &color)
{

    if (color == Color::Red) return ROUGE;
    else if (color == Color::Blue) return BLEU;
    else if (color == Color::Green) return VERT;
    else if (color == Color::Black) return NOIR;
    else if (color == Color::White) return BLANC;
    else if (color == Color::Yellow) return JAUNE;
    else return "";
}

void debug(string text)
{
    if (DEBUG != 0)
    {
        SetColor(3);
        cout << text << endl << std::flush;
        SetColor(15);
    }
}

string sizeToString(size_t sz) {


  stringstream ss;


  ss << sz;


  return ss.str();

}

