#include "interpreteur.cpp"
#include <cstdlib>


/** FONCTIONS **/

/* Gestion des evenements de la fenetre Window */
void handle_events(const shared_ptr<sf::RenderWindow> &window);

/* Configuration de Window */
void config_window(const std::shared_ptr<sf::RenderWindow> &window);

/* Message de demarrage */
void start();

/* Message d'erreur */
void error(string message);

/* Message d'arret */
void exit();

/** MAIN **/

int main()
{

    /* Création de la fenêtre*/
    const auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "", sf::Style::None);
    config_window(window);

    /* GERER LES EVENEMENTS DE LA FENETRE */
    std::thread handle(handle_events,window);

    /* PERSISTENCE */
    auto disk = std::make_shared<Persistence<string, Forme<int>>>();

    /* INTERPRETEUR */
    std::unique_ptr<Interpreteur<string,int>> interp = nullptr;

    /* START */
    start();

    while (true)
    {

        try
        {
            /* Creer un nouvel interpreteur, detruire le précédent */
            interp = std::make_unique<Interpreteur<string,int>>(window,disk);

            /* Lire la commande entree par l'utilisateur */
            interp->lire();

            /* Executer la commande */
            interp->executer();

            /* Reinitialiser */
            interp.reset();

        }
        catch (string message)
        {
            /* En cas de problème, capter le message du problème, l'afficher et terminer dans un état sain */

            if (message != EXIT)
            {
                error(message); // Message d'erreur
            }
            else
            {
                exit(); // Signal d'exit
                handle.join();
                return 0;
            }
        }

        catch ( const std::exception& e )
        {
            // standard exceptions
            SetColor(4);
            cout << e.what() << endl;
        }

    }

    /* STOP HANDLE */
    handle.join();

    return 0;

}

/**================================================================================**/

/** Source : tutoriel SFML **/
void handle_events(const shared_ptr<sf::RenderWindow> &window)
{
	// on fait tourner le programme tant que la fenêtre n'a pas été fermée
	 while (window->isOpen()){

	 	// on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
    sf::Event event;
    while (window->pollEvent(event))
    {
        // check the type of the event...
        switch (event.type)
        {
        // fermeture de la fenêtre lorsque l'utilisateur le souhaite
        case sf::Event::Closed:
            window->close();
            break;
        // key pressed
        case sf::Event::KeyPressed:
            break;

        // we don't process other types of events
        default:
            break;
        }
    }
}
}

void config_window(const std::shared_ptr<sf::RenderWindow> &window)
{
    sf::Vector2i pos(WINDOW_POS_X,WINDOW_POS_Y);
    window->setActive(false);
    window->setFramerateLimit(FRAME_RATE_LIMIT);
    window->setMouseCursorVisible(false);
    window->setVerticalSyncEnabled(true);
    window->setPosition(pos);
    window->display(); //affichage
}

void start()
{
    SetColor(8);
    cout << START_MSG_4 << endl;
    cout << START_MSG << endl;
    cout << START_MSG_1 << endl;
    cout << START_MSG_2 << endl;
    cout << START_MSG_3 << endl;
    cout << START_MSG_5 << endl;
    cout << START_MSG_4 << endl;
    SetColor(15);
}

void error(string message){
    SetColor(12);
    cout << message << endl;
    SetColor(15);
}

void exit()
{
    SetColor(15);
    cout << EXIT_CMD_MSG << endl;
}
