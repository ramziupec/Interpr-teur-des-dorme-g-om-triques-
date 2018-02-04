#include "interpreteur.h"
#include "rectangle.cpp"
#include "cercle.cpp"
#include "polygone.cpp"
#include "forme.cpp"
#include "persistence.cpp"

constexpr unsigned int hashed(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (hashed(str, h+1) * 33) ^ str[h];
}

template <typename C, typename E>
Interpreteur<C,E>::Interpreteur(const shared_ptr<sf::RenderWindow>& window,const shared_ptr<Persistence<C,Forme<E>>>& persistance)
{
    this->window = window;
    this->persistance = persistance;
    this->command = "";
    this->keyword = "";
    this->isstream.str("");
    this->m1 = 0;
    this->m2 = 0;
    this->endofcommand = false;
}

template <typename C, typename E>
Interpreteur<C,E>::~Interpreteur()
{
    window.reset();
    persistance.reset();
}


template <typename C, typename E>
void Interpreteur<C,E>::lire()
{
    SetColor(30);
    cout << "> ";
    getline(cin, command);
    isstream.str(command);
    if (command == EXIT)
    {
        throw string(EXIT_CMD_MSG);
    }
    SetColor(15);
}

// interpreter une chaine de caractères
template <typename C, typename E>
string Interpreteur<C,E>::interpreter()
{
    string word = "";
    getline(isstream, word, ' ');

    if (word != "" && endofcommand)
    {
        throw string(SUPERFLUX_CHAIN) + string(word);
    }

    if ( word == "" && !endofcommand)
    {
        throw string(PARAMETRE_MANQUANT);
    }

    return word;
}

// interpreter un chaine comme un entier
template <typename C, typename E>
int Interpreteur<C,E>::interpreterint()
{
    int nbr;
    try
    {
        nbr = atoi( interpreter().c_str() );

        // tous les entiers doivent etre positifs
        if (nbr < 0)
        {
            throw string(NOMBRE_INVALIDE);
        }
    }
    catch (std::exception const & e)
    {
        throw string(NOMBRE_INVALIDE);
    }
    return nbr;
}

template <typename C, typename E>
void Interpreteur<C,E>::parse()
{

    // lire le type de la forme

    form_type = interpreter();


    if ( string(form_type) != string(RECTANGLE) &&
            string(form_type) != string(CERCLE) &&
            string(form_type) != string(POLYGONE))
    {
        throw string(FORME_INCONNUE) + string(form_type);
    }

    // lire le id de la forme

    form_id = interpreter();

    // lire les couleurs

    col_f = getColorByName(interpreter());
    col_b = getColorByName(interpreter());

    // lire l'epaisseur et les positions

    if ( (epai = interpreterint()) > MAX_FORM_BORD_SIZE )
    {
        throw string(MAX_BORD_SIZE_MSG) + string (MAX_BORD_SIZE_MSG);
    } ;

    if ( (x = interpreterint()) > WINDOW_SIZE_X)
    {
        throw string(WINDOW_OVERFLOW_ORIGIN);
    }

    if ( (y = interpreterint()) > WINDOW_SIZE_Y)
    {
        throw string(WINDOW_OVERFLOW_ORIGIN);
    }

    /** lire les parametres extra **/

    // rectangle ou polygone, 2 parametres
    if (string(form_type) == string(RECTANGLE))
    {
        m1 = interpreterint();
        m2 = interpreterint();

        if (m1 <= m2)
        {
            throw string(LONGUEUR_INF_LARGEUR);
        }
    }
    else if (string(form_type) == string(CERCLE))
    {
        m1 = interpreterint();
    }
    else if(string(form_type) == string(POLYGONE)){
        m1 = interpreterint();
        if ( (m2 = interpreterint()) < 3 ){
             throw new string(NOT_A_POLYGON);
        };
    }

    else {
        throw string(FORME_INCONNUE) + string(form_type);
    }

    /** Terminer la commande **/
    terminateCommand();

}


template <typename C, typename E>
void Interpreteur<C,E>::executer()
{

    // lire la commande
    keyword = interpreter();

    // case
    switch ( hashed(keyword.c_str()) )
    {
     // help
    case hashed(HELP) :
    {
        terminateCommand();

        help();
        break;
    }
    // create
    case hashed(CREATE) :

        // lire les données communes
        parse();

        switch( hashed(form_type.c_str()) )
        {

        // rectangle
        case hashed(RECTANGLE) :
        {

            // creer le rectangle
            Rectangle<int> forme(x,y,epai,col_f,col_b,m1,m2);
            forme >> window;

            // ajouter à la persistence
            shared_ptr<Rectangle<int>> ptr = std::make_shared<Rectangle<int>>(forme);
            (*persistance)(form_id, ptr, window);

            break;

        }

        // case cercle
        case hashed(CERCLE):
        {

            // creer le cercle
            Cercle<int> forme(x,y,epai,col_f,col_b,m1);
            forme >> window;

            // ajouter à la persistence
            shared_ptr<Cercle<int>> ptr = std::make_shared<Cercle<int>>(forme);
            (*persistance)(form_id, ptr, window);

            break;

        }

        // polygone
        case hashed(POLYGONE) :
        {

            // creer le polygone
            Polygone<int> forme(x,y,epai,col_f,col_b,m1,m2);
            forme >> window;

            // ajouter à la persistence
            shared_ptr<Polygone<int>> ptr = std::make_shared<Polygone<int>>(forme);
            (*persistance)(form_id, ptr, window);

            break;
        }


        default :
            throw string(FORME_INCONNUE) + string(form_type);
            break;

        }
        break;

     // move
    case hashed(MOVE) :
    {
        keyword = interpreter();
        x = interpreterint();
        y = interpreterint();
        terminateCommand();

        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];
        *ptr << sf::Vector2f((double) x, (double) y);
        *persistance >> window;
        break;

    }

    //rotate
    case hashed(ROTATE) :
    {
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        keyword = interpreter();

        m1 = interpreterint();
        terminateCommand();

         if (keyword == string(PLUS)) {

            *ptr = (*ptr) + m1;
         }

         if (keyword == string(MOINS)){

            *ptr = (*ptr) - m1;
         }

        *persistance >> window;
        break;
    }
    //Color
    case hashed(COLOR) :
    {
        bool decision;
        keyword = interpreter();
        if ( keyword == CONTOUR )
		       decision = true;
        else if (keyword == BACKGROUND)
		       decision = false;
        else
		     throw string(NO_CONTOUR_BACKGROUNG_ARG) + CONTOUR + string(" ou ") + BACKGROUND;
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];
        keyword = interpreter();

        terminateCommand();

        *ptr << Couleur( getColorByName(keyword), decision);
        *persistance >> window;
        break;
    }

    //Incrémenter ou decrementer la bordure
    case hashed(CONTOUR) :
    {
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        keyword = interpreter();

        terminateCommand();

         if (keyword == string(PLUS_PLUS)) {
            ++*ptr;
         }

         if (keyword == string(MOINS_MOINS)){
            --*ptr;
         }

        *persistance >> window;
        break;
    }
       // scale
    case hashed(SCALEUP) :
    {
        keyword = interpreter();
        m1 = interpreterint();
        terminateCommand();

        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];
        *ptr = *ptr * m1;
        *persistance >> window;
        break;

    }

    // scale
    case hashed(SCALEDOWN) :
    {
        keyword = interpreter();
        m1 = interpreterint();
        terminateCommand();

        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];
        *ptr = *ptr / m1;
        *persistance >> window;
        break;

    }
        //Get Superficie d'une forme
    case hashed(SUPERFICIE) :
    {
        keyword = interpreter();
        terminateCommand();

        //cout<<keyword<<endl;
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];


        if ( typetest<Rectangle<int>>(*ptr) ){
            cout << (dynamic_cast<Rectangle<int>&>(*ptr)).superficie();
        }

        if ( typetest<Cercle<int>>(*ptr) ){
            cout << (dynamic_cast<Cercle<int>&>(*ptr)).superficie();
        }

        if ( typetest<Polygone<int>>(*ptr) ){
            cout << (dynamic_cast<Polygone<int>&>(*ptr)).superficie();
        }

        cout << endl;
        break;

    }

    //Get Perimetre d'une forme
    case hashed(PERIMETRE) :
    {
        keyword = interpreter();
        terminateCommand();

        //cout<<keyword<<endl;
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        //Rectangle<int> copie;
        if ( typetest<Rectangle<int>>(*ptr) ){
            cout << (dynamic_cast<Rectangle<int>&>(*ptr)).perimetre();
        }

         if ( typetest<Cercle<int>>(*ptr) ){
            cout << (dynamic_cast<Cercle<int>&>(*ptr)).perimetre();
        }

         if ( typetest<Polygone<int>>(*ptr) ){
            cout << (dynamic_cast<Polygone<int>&>(*ptr)).perimetre();
        }
        cout << endl;
        break;
    }

    // copy
    case hashed(COPY) :
    {
        // lire forme originale
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        //cout << typeid(*ptr).name() << endl;

        // lire id copie
        keyword = interpreter();
        shared_ptr<Forme<int>> ptrcopie;

        x = interpreterint();
        y = interpreterint();

        terminateCommand();

        // copier
        if ( typetest<Rectangle<int>>(*ptr) )
        {
            Rectangle<int> copie = dynamic_cast<Rectangle<int>&>(*ptr);
            ptrcopie = make_shared<Rectangle<int>>(copie);
        }

        if ( typetest<Cercle<int>>(*ptr) )
        {
            Cercle<int> copie = dynamic_cast<Cercle<int>&>(*ptr);
            ptrcopie = make_shared<Cercle<int>>(copie);
        }

         if ( typetest<Polygone<int>>(*ptr) )
        {
            Polygone<int> copie = dynamic_cast<Polygone<int>&>(*ptr);
            ptrcopie = make_shared<Polygone<int>>(copie);
        }


        *ptrcopie = *ptrcopie << sf::Vector2f((double) x, (double) y);

        //ptrcopie = &copie;
        (*persistance)(keyword, ptrcopie, window);
        *persistance >> window;
        break;

    }

      // list
    case hashed(LIST) :
    {
        terminateCommand();

        cout << persistance;
        break;
    }

        // comparer entre les formes selon la superficie
    case hashed(TEST) :
    {
        //lire l'id de la premiere forme
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr1 = (*persistance)[keyword];

        //lire l'operateur de comparaison
        keyword = interpreter();
        string op = keyword;

        // lire l’id de la deuxieme forme
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr2 = (*persistance)[keyword];

        terminateCommand();

        string reponse;

        if (op == string(SUPERIEUR)) *ptr1>*ptr2 ? reponse = TRUE : reponse = FALSE;
        else if (op == string(INFERIEUR)) *ptr1<*ptr2 ? reponse = TRUE : reponse = FALSE;
        else if (op == string(EGALE)) *ptr1==*ptr2 ? reponse = TRUE : reponse = FALSE;
        else throw string(UNKNOWN_OPERATOR) + string(op);

        cout << reponse << endl;

        break;
    }

    // test
    case hashed(TEST_RECTANGLE) :
    {

        terminateCommand();

        // creer le rectangle
        Rectangle<int> forme(20,20,1,sf::Color::Red,sf::Color::Green,20,20);
        forme >> window;

        // ajouter à la persistence
        shared_ptr<Rectangle<int>> ptr = std::make_shared<Rectangle<int>>(forme);
        (*persistance)(TEST_RECTANGLE, ptr, window);

        break;
    }

    // test
    case hashed(TEST_CERCLE) :
    {

        terminateCommand();

        // creer le rectangle
        Cercle<int> forme(70,10,2,sf::Color::Blue,sf::Color::Magenta,50);
        forme >> window;

        // ajouter à la persistence
        shared_ptr<Cercle<int>> ptr = std::make_shared<Cercle<int>>(forme);
        (*persistance)(TEST_CERCLE, ptr, window);

        break;
    }

    // test
    case hashed(TEST_POLYGONE) :
    {

        terminateCommand();

        // creer le rectangle
        Polygone<int> forme(100,120,3,sf::Color::White,sf::Color::Yellow,20,5);
        forme >> window;

        // ajouter à la persistence
        shared_ptr<Polygone<int>> ptr = std::make_shared<Polygone<int>>(forme);
        (*persistance)(TEST_POLYGONE, ptr, window);

        break;
    }

    case hashed(TESTCASE) :
    {
        terminateCommand();

        // creer le rectangle
        Rectangle<int> forme(10,10,3,sf::Color::Red,sf::Color::Green,20,20);
        Rectangle<int> copie = forme;

        copie << sf::Vector2f(100,100);
        forme >> window;
        copie >> window;

        // ajouter à la persistence
        shared_ptr<Rectangle<int>> ptr = std::make_shared<Rectangle<int>>(forme);
        (*persistance)(TEST_RECTANGLE, ptr, window);

        shared_ptr<Rectangle<int>> ptr2 = std::make_shared<Rectangle<int>>(copie);
        (*persistance)("copie", ptr2, window);

        break;
    }

    // distance
    case hashed(DIST) :
    {
        //lire l'id de la premiere forme
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr1 = (*persistance)[keyword];

        // lire l’id de la deuxieme forme
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr2 = (*persistance)[keyword];

        terminateCommand();

        cout << *ptr1 % *ptr2 << endl;

        break;
    }

    // remove
    case hashed(REMOVE) :
    {

        keyword = interpreter();
        terminateCommand();

        persistance->supprimer(keyword, window);

        break;
    }

    // cls
    case hashed(CLS) :
    {
        terminateCommand();
        system("cls");
        break;
    }


    // default
    default :
        throw string(COMMANDE_INCONNUE) + keyword;
        break;

    }

    // reset command
    command = "";

}


template <typename C, typename E>
void Interpreteur<C,E>::terminateCommand()
{
    endofcommand = true;
    interpreter();

}

template <typename C, typename E>
void Interpreteur<C,E>::help()
{
    SetColor(8);
    cout << " [C O M M A N D E S]" << endl;
    SetColor(15);
    cout << HELP << endl;
    cout << CREATE + string(" [Forme_Type] [Forme_ID] [Coul_Fond] [Coul_Contour] [Epaisseur] [Position x] [Position y] <metriques*>") << endl;
    cout << MOVE + string(" [Forme_ID] [poision_x] [position_y]") << endl;
    cout << ROTATE + string(" [Forme_ID] {+|-} [angle_rotation]") << endl;
    cout << COLOR + string(" {background|contour} [Forme_ID] [Coul_ID]") << endl;
    cout << CONTOUR + string(" [Forme_ID] {++|--}") << endl;
    cout << SCALEUP + string(" [Forme_ID] [facteur_echelle]") << endl;
    cout << SCALEDOWN + string(" [Forme_ID] [facteur_echelle]") << endl;
    cout << PERIMETRE + string(" [Forme_ID] ") << endl;
    cout << SUPERFICIE + string(" [Forme_ID] ") << endl;
    cout << COPY + string(" [Forme_ID] [New_Forme_ID] [poision_x] [position_y]") << endl;
    cout << LIST << endl;
    cout << TEST + string(" [Forme_ID_1] {>|<|==} [Forme_ID_2]") << endl;
    cout << DIST + string(" [Forme_ID_1][Forme_ID_2]") << endl;
    cout << REMOVE + string(" [Forme_ID] ") << endl;
    cout << CLS << endl;
    cout << EXIT << endl;
    cout << endl;
    SetColor(8);
    cout << " [F O R M E S      E T     M E T R I Q U E S]" << endl;
    SetColor(15);
    cout << "Forme_Type = " + string(RECTANGLE) + "|" + string(CERCLE) + "|" + string(POLYGONE) << endl;
    cout << "Metriques d'un " + string(RECTANGLE) + " : " + " [Longeur] [Largeur]" << endl;
    cout << "Metriques d'un " + string(CERCLE) + " : " + " [Rayon]" << endl;
    cout << "Metriques d'un " + string(POLYGONE) + " : " + " [Rayon] [Nb_Sommets]" << endl;
    cout << endl;
    SetColor(8);
    cout << " [C O U L E U R S]" << endl;
    SetColor(15);
    cout << "{Coul_Fond|Coul_Contour[Coul_ID} = " + string(ROUGE) + "|" + string(VERT) + "|" + string(BLEU) + "|"
     + string(NOIR) + "|" + string(BLANC) + "|" + string(JAUNE)  << endl;
    cout << endl;
}



